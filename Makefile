include config.mk

.PHONY: all build clean run assignment5 always run

all: clean build

#
# BUILD
#
build: $(BUILD_DIR)/assignment5.out

$(BUILD_DIR)/assignment5.out: always
	@$(MAKE) -C JackWilliamson_Assignment5/src BUILD_DIR=$(abspath $(BUILD_DIR))

#
# RUN
#
run: build
	@$(BUILD_DIR)/assignment5.out

#
# Clean
#
clean:
	@rm -rf $(BUILD_DIR)

always:
	@mkdir -p $(BUILD_DIR)