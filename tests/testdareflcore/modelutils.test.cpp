// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <darefl/model/modelutils.h>

//! Tests of Utils namespace functions.

class ModelUtilsTest : public ::testing::Test
{
public:
    ~ModelUtilsTest();
};

ModelUtilsTest::~ModelUtilsTest() = default;

//! Testing helper structure.

TEST_F(ModelUtilsTest, CreateDiffVector)
{
    std::vector<double> a{1.0, 2.0};
    std::vector<double> b{1.0, 4.0, 3.0};

    auto result = Utils::CreateDiffVector(a, b);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0 * (2.0 - 4.0) / (2.0 + 4.0));
}
