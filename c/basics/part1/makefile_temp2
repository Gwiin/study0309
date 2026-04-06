TARGET = hello limit literal charNumber stringCopy oddEven triangle compare compare2

all: ${TARGET} # make all을 명시해야하지만 처음에 명시하면 make만 했을때도 가능

hello : $@ #앞의 hello를 찾아.c를 붙임
limit : $@
literal : $@
charNumber : $@
stringCopy : $@
oddEven : $@
triangle : $@
compare : $@
compare2 : $@

# cc -o hello hello.c 실행파일과 c파일의 이름이 같으면 생략가능
# 파일이 수정된 날짜와 시간을 체크하기때문에 수정하고 바로 make 해도 적용이 된다

clean : 
	rm ${TARGET}

