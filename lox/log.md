the main last issue is that we can't cast std::any smart_pointers, so all the tests in ast_tests don't work
solution ? -  we might have to experiment and create a wrapper/type that accepts any and can help, just make it a class to reuse
