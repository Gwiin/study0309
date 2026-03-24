#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "MQTTClient.h"

#define SUBNET_PREFIX "163.152.213."
#define PORT "1883"
#define TOPIC "school/test"
#define QOS 1
#define TIMEOUT 10000L

#define MAX_BROKERS 20
#define MAX_INPUT 256
#define MAX_ADDRESS 128
#define MAX_CLIENTID 128

/* -------------------- 공통 유틸 함수 -------------------- */

void trim_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int is_quit_command(const char *str) {
    return strcmp(str, "q") == 0;
}

int is_valid_suffix(const char *suffix) {
    if (strlen(suffix) == 0) {
        return 0;
    }

    for (int i = 0; suffix[i] != '\0'; i++) {
        if (!isdigit((unsigned char)suffix[i])) {
            return 0;
        }
    }

    int value = atoi(suffix);
    if (value < 0 || value > 255) {
        return 0;
    }

    return 1;
}

void build_address(char *address, const char *suffix) {
    int value = atoi(suffix);
    snprintf(address, MAX_ADDRESS, "tcp://%s%d:%s", SUBNET_PREFIX, value, PORT);
}

void make_client_id(char *client_id, const char *tag, int index) {
    long t = (long)time(NULL);
    snprintf(client_id, MAX_CLIENTID, "client_%s_%d_%ld", tag, index, t);
}

/* -------------------- MQTT 전송 함수 -------------------- */

int send_message_to_broker(const char *address, const char *message, const char *client_tag, int index) {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    char client_id[MAX_CLIENTID];

    make_client_id(client_id, client_tag, index);

    MQTTClient_create(&client, address, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        printf("[실패] 브로커 접속 실패: %s\n", address);
        MQTTClient_destroy(&client);
        return 0;
    }

    pubmsg.payload = (void *)message;
    pubmsg.payloadlen = (int)strlen(message);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    if (MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token) != MQTTCLIENT_SUCCESS) {
        printf("[실패] 메시지 전송 실패: %s\n", address);
        MQTTClient_disconnect(client, TIMEOUT);
        MQTTClient_destroy(&client);
        return 0;
    }

    MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("[성공] 전송 완료 -> %s\n", address);

    MQTTClient_disconnect(client, TIMEOUT);
    MQTTClient_destroy(&client);

    return 1;
}

/* -------------------- 입력 관련 함수 -------------------- */

void input_line(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    trim_newline(buffer);
}

int input_single_suffix(char *suffix) {
    while (1) {
        input_line("브로커 마지막 3자리 입력 (예: 106, q: 메인으로): ", suffix, MAX_INPUT);

        if (is_quit_command(suffix)) {
            return 0;
        }

        if (!is_valid_suffix(suffix)) {
            printf("잘못된 입력입니다. 0~255 범위의 숫자만 입력하세요.\n");
            continue;
        }

        return 1;
    }
}

int input_multiple_suffixes(char suffixes[][MAX_INPUT], int *count) {
    char input[MAX_INPUT];
    *count = 0;

    printf("\n보낼 브로커들의 마지막 3자리를 입력하세요.\n");
    printf("입력을 마치려면 done, 메인으로 돌아가려면 q 를 입력하세요.\n");

    while (1) {
        input_line("브로커 마지막 3자리 입력: ", input, MAX_INPUT);

        if (strcmp(input, "q") == 0) {
            *count = 0;
            return 0;
        }

        if (strcmp(input, "done") == 0) {
            if (*count == 0) {
                printf("최소 1개 이상의 주소를 입력해야 합니다.\n");
                continue;
            }
            return 1;
        }

        if (!is_valid_suffix(input)) {
            printf("잘못된 입력입니다. 0~255 범위의 숫자만 입력하세요.\n");
            continue;
        }

        if (*count >= MAX_BROKERS) {
            printf("최대 %d개까지만 입력 가능합니다.\n", MAX_BROKERS);
            return 1;
        }

        strcpy(suffixes[*count], input);
        (*count)++;
        printf("추가됨: %s\n", input);
    }
}

/* -------------------- 채팅 모드 함수 -------------------- */

void one_to_one_chat(void) {
    char suffix[MAX_INPUT];
    char address[MAX_ADDRESS];
    char message[MAX_INPUT];

    printf("\n===== 1대1 채팅 =====\n");

    if (!input_single_suffix(suffix)) {
        printf("메인 메뉴로 돌아갑니다.\n");
        return;
    }

    build_address(address, suffix);
    printf("선택된 브로커 주소: %s\n", address);
    printf("q 입력 시 메인 메뉴로 돌아갑니다.\n");

    while (1) {
        input_line("메세지 입력 : ", message, MAX_INPUT);

        if (is_quit_command(message)) {
            printf("메인 메뉴로 돌아갑니다.\n");
            break;
        }

        if (strlen(message) == 0) {
            printf("빈 메시지는 전송할 수 없습니다.\n");
            continue;
        }

        send_message_to_broker(address, message, "single", 0);
    }
}

void group_chat(void) {
    char suffixes[MAX_BROKERS][MAX_INPUT];
    char addresses[MAX_BROKERS][MAX_ADDRESS];
    char message[MAX_INPUT];
    int count = 0;

    printf("\n===== 전체 채팅 =====\n");

    if (!input_multiple_suffixes(suffixes, &count)) {
        printf("메인 메뉴로 돌아갑니다.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        build_address(addresses[i], suffixes[i]);
    }

    printf("\n등록된 브로커 목록:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, addresses[i]);
    }

    printf("q 입력 시 메인 메뉴로 돌아갑니다.\n");

    while (1) {
        input_line("메세지 입력 : ", message, MAX_INPUT);

        if (is_quit_command(message)) {
            printf("메인 메뉴로 돌아갑니다.\n");
            break;
        }

        if (strlen(message) == 0) {
            printf("빈 메시지는 전송할 수 없습니다.\n");
            continue;
        }

        for (int i = 0; i < count; i++) {
            send_message_to_broker(addresses[i], message, "group", i);
        }
    }
}

/* -------------------- 메뉴 함수 -------------------- */

void print_menu(void) {
    printf("\n====================\n");
    printf("1. 1대1 채팅\n");
    printf("2. 전체 채팅\n");
    printf("3. 종료\n");
    printf("====================\n");
}

int main(void) {
    char input[MAX_INPUT];
    int menu;

    while (1) {
        print_menu();
        input_line("메뉴 선택 : ", input, MAX_INPUT);

        if (strlen(input) == 0) {
            printf("메뉴를 입력하세요.\n");
            continue;
        }

        menu = atoi(input);

        switch (menu) {
            case 1:
                one_to_one_chat();
                break;

            case 2:
                group_chat();
                break;

            case 3:
                printf("프로그램을 종료합니다.\n");
                return 0;

            default:
                printf("잘못된 메뉴입니다. 다시 입력하세요.\n");
                break;
        }
    }

    return 0;
}