.PHONY: test
test: $(TEST_EXE_PATH)
	sh $(BASE_PATH)/test/sh/test_$(TEST_TYPE).sh $(TEST_EXE_PATH) $(TEST_DATA_PATH) $(CURRENT_PATH)
