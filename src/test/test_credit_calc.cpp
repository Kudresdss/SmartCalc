#include "test_core.h"

TEST(CREDIT_CALCULATOR, ANNUITY) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "", "", false, false, false, "", "",
            0, 0, 0, 0, 0,
            true, false,
            1000000, 12, 8
    };
    ModelInfo test_model_info = test_model->slotCreditToModel(test_view_info);
    ASSERT_NEAR(test_model_info.credit_table[0][1], 86988.43, 1e-2);
    ASSERT_NEAR(test_model_info.total_interest, 43861.15, 1e-2);
    ASSERT_NEAR(test_model_info.total_payment, 1043861.16, 1e-2);
}

TEST(CREDIT_CALCULATOR, DIFFERENTIATED) {
    Model* test_model = &Model::getInstance();
    ViewInfo test_view_info = {
            "", "", false, false, false, "", "",
            0, 0, 0, 0, 0,
            false, true,
            1000000, 12, 8
    };
    ModelInfo test_model_info = test_model->slotCreditToModel(test_view_info);
    ASSERT_NEAR(test_model_info.credit_table[1][1], 89444.44, 1e-2);
    ASSERT_NEAR(test_model_info.total_interest, 43333.33, 1e-2);
    ASSERT_NEAR(test_model_info.total_payment, 1043333.33, 1e-2);
}
