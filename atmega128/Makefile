BUILD_DIR := build
CMAKE := cmake
PROGRAM ?=

.PHONY: all configure upload list clean rebuild

all: configure
	$(CMAKE) --build $(BUILD_DIR)

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -G "Unix Makefiles" \
		-DCMAKE_TOOLCHAIN_FILE=$(CURDIR)/avr-toolchain.cmake

upload: configure
	@if [ -z "$(PROGRAM)" ]; then \
		echo "PROGRAM 이름이 필요합니다."; \
		echo "예시: make upload PROGRAM=timer2ledleftright"; \
		echo "또는: make upload_timer2ledleftright"; \
		echo "가능한 업로드 타겟 목록은 'make list' 로 확인하세요."; \
		exit 2; \
	fi
	$(CMAKE) --build $(BUILD_DIR) --target upload_$(PROGRAM)

upload_%: configure
	$(CMAKE) --build $(BUILD_DIR) --target upload_$*

list: configure
	@$(CMAKE) --build $(BUILD_DIR) --target help | grep 'upload_'

clean:
	@if [ -d "$(BUILD_DIR)" ]; then \
		$(CMAKE) --build $(BUILD_DIR) --target clean; \
	fi

rebuild: configure
	$(CMAKE) --build $(BUILD_DIR) --clean-first
