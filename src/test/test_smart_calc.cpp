#include "test_core.h"

TEST(SMART_CALCULATOR_INPUT_TOKENS, CONSTANTS_FRACTIONAL_NUMBER) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1.2345678",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1.2345678, 1e-7);
}

TEST(SMART_CALCULATOR_INPUT_TOKENS, CONSTANTS_EXPONENTIAL_NOTATION_POSITIVE) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "10E+2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1000., 1e-7);
}

TEST(SMART_CALCULATOR_INPUT_TOKENS, CONSTANTS_EXPONENTIAL_NOTATION_NEGATIVE) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "10E-2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 0.1, 1e-7);
}

TEST(SMART_CALCULATOR_INPUT_TOKENS, CONSTANTS_PI) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "π",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 3.1415927, 1e-7);
}

TEST(SMART_CALCULATOR_INPUT_TOKENS, CONSTANTS_E) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "e",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 2.7182818, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BRACKETS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 * (1 + 2)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 3., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BRACKETS_POSITIVE_EXPRESSION) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "+(5)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 5, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BRACKETS_NEGATIVE_EXPRESSION) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "-(5)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, -5, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BINARY_OPERATIONS_PLUS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 + 2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 3., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BINARY_OPERATIONS_MINUS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 - 2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, -1., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BINARY_OPERATIONS_MULTIPLY) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 * 2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 2., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BINARY_OPERATIONS_DIVIDE) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 / 2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 0.5, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BINARY_OPERATIONS_EXPONENTIATION) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "2 ^ 2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 4, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, BINARY_OPERATIONS_MODULUS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "8mod(7)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_SIN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "sin(π / 2)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_COS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "cos(2 * π)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_TAN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "tan(π / 4)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_ASIN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "asin(1)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1.5707963, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_ACOS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "acos(1)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 0., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_ATAN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "atan(π)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1.2626273, 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_SQRT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "√(4)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 2., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_LOG10) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "log(10)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1., 1e-7);
}

TEST(SMART_CALCULATOR_OPERATIONS, UNARY_OPERATIONS_LN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "ln(e)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 1., 1e-7);
}

TEST(SMART_CALCULATOR_ERRORS, UNKNOWN_TOKEN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "unknown token",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: unknown token");
}

TEST(SMART_CALCULATOR_ERRORS, NUMBER_CONTAINS_MORE_THAN_ONE_DOT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1.....2",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: number contains more than one dot");
}

TEST(SMART_CALCULATOR_ERRORS, BRACKETS_NOT_PAIRED) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            " (1)+ 2) ",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of brackets: some brackets are not in pair");
}

TEST(SMART_CALCULATOR_ERRORS, OPENING_BRACKET_IN_THE_END) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1) (",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of brackets: opening bracket in the end of expression");
}

TEST(SMART_CALCULATOR_ERRORS, CLOSING_BRACKET_IN_THE_BEGINNING) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            ") 1( 1",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of brackets: closing bracket in the beginning of expression");
}

TEST(SMART_CALCULATOR_ERRORS, BINARY_FUNCTION_IN_THE_BEGINNING) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "^3",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of functions: binary function in the beginning of expression");
}

TEST(SMART_CALCULATOR_ERRORS, BINARY_FUNCTION_IN_THE_END) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 +",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of functions: binary function in the end of expression");
}


