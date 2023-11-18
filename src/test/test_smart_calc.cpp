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

TEST(SMART_CALCULATOR_INPUT_TOKENS, MINOR_INPUT_FEATURES) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "(+e)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    test_model_info = test_model->slotSmartToModel(test_view_info);
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

TEST(SMART_CALCULATOR_EQUATIONS, COMPLEX_EQUATION_WITHOUT_X) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "(√(ln(7)*7^(π)))/(atan(π/4))^(sin(45))",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 41.9150752, 1e-7);
}

TEST(SMART_CALCULATOR_EQUATIONS, COMPLEX_EQUATION_WITH_X) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "(√(ln(7)*7^(π)))/(atan(π/4))^(sin(45))/x^(x)",
            "atan(e)",
            true,
            true,
            true
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 32.9537425, 1e-7);
}

TEST(SMART_CALCULATOR_EQUATIONS, COMPLEX_EQUATION_WITHOUT_X_ALL_FUNCTIONS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "(ln(7^(6))*log(7))+(sin(π)-cos(π)-asin(1)-acos(1))*(tan(π)/atan(π/4))*√(4mod(2))+(π*e*1.25)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 20.5415769, 1e-7);
}

TEST(SMART_CALCULATOR_EQUATIONS, COMPLEX_EQUATION_WITH_X_ALL_FUNCTIONS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "(ln(7^(6))*log(7))+(sin(x)-cos(π)-asin(1)-acos(1))*(tan(x)/atan(π/4))*√(4mod(x))+(π*e*1.25)",
            "sin(π/4)",
            true,
            true,
            true
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_NEAR(test_model_info.result, 20.6105401, 1e-7);
}

TEST(SMART_CALCULATOR_EQUATIONS, Y_OUT_OF_BOUNDS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "x^(x)",
            "tan(e)",
            true,
            true,
            true
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(std::to_string(test_model_info.result), std::to_string(std::numeric_limits<double>::quiet_NaN()));
}

TEST(SMART_CALCULATOR_TOKEN_ERRORS, UNKNOWN_TOKEN) {
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

TEST(SMART_CALCULATOR_TOKEN_ERRORS, NUMBER_CONTAINS_MORE_THAN_ONE_DOT) {
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

TEST(SMART_CALCULATOR_BRACKET_ERRORS, BRACKETS_NOT_PAIRED) {
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

TEST(SMART_CALCULATOR_BRACKET_ERRORS, EMPTY_BRACKETS) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "()",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of brackets: empty brackets");
}

TEST(SMART_CALCULATOR_BRACKET_ERRORS, OPENING_BRACKET_IN_THE_END) {
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

TEST(SMART_CALCULATOR_BRACKET_ERRORS, CLOSING_BRACKET_IN_THE_BEGINNING) {
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

TEST(SMART_CALCULATOR_EQUATION_CONSTRUCTION_ERRORS, BINARY_FUNCTION_IN_THE_BEGINNING) {
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

TEST(SMART_CALCULATOR_EQUATION_CONSTRUCTION_ERRORS, BINARY_FUNCTION_IN_THE_END) {
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

TEST(SMART_CALCULATOR_EQUATION_CONSTRUCTION_ERRORS, UNARY_FUNCTION_IN_THE_END) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1sin",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of functions: unary function in the end of expression");
}

TEST(SMART_CALCULATOR_EQUATION_CONSTRUCTION_ERRORS, TWO_CONSECUTIVE_BINARY_FUNCTIONS) {
Model* test_model = &Model::getInstance();
ViewInfo test_view_info = {
        "1^^2",
        "",
        true,
        false,
        false
};
ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of functions: two consecutive binary functions");
}

TEST(SMART_CALCULATOR_EQUATION_CONSTRUCTION_ERRORS, BINARY_FUNCTION_AFTER_AN_UNARY) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "sin mod",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: incorrect usage of functions: binary function after an unary function");
}

TEST(SMART_CALCULATOR_EQUATION_CONSTRUCTION_ERRORS, CERTAIN_MULTIPLICATION_WITHOUT_A_TOKEN) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "xx",
            "1",
            true,
            true,
            true
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error.empty(), 0);
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, INVALID_ASIN_INPUT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "asin(20)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: asin of a number ∉ [-1;1]");
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, INVALID_ACOS_INPUT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "acos(20)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: acos of a number ∉ [-1;1]");
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, INVALID_LOG10_INPUT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "log(0)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: log of a number ∈ (-∞;0]");
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, INVALID_LN_INPUT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "ln(0)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: ln of a number ∈ (-∞;0]");
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, INVALID_SQRT_INPUT) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "√(-1)",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: square root of a negative number");
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, DIVISION_BY_ZERO) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 / 0",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: division by zero");
}

TEST(SMART_CALCULATOR_INVALID_FUNCTION_INPUT_ERRORS, MODULUS_OF_DIVISION_BY_ZERO) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "1 mod 0",
            "",
            true,
            false,
            false
    };
    ModelInfo test_model_info = test_model->slotSmartToModel(test_view_info);
    ASSERT_EQ(test_model_info.error, "Runtime error: invalid expression: modulus of division by zero");
}
