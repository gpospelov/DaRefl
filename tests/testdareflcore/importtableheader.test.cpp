// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <darefl/dataloader2/dataloader_constants.h>
#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/importtableheader.h>
#include <mvvm/model/comboproperty.h>

using namespace DataLoader;

//! Test the data column item
class ImportTableHeaderTest : public ::testing::Test
{
public:
    ~ImportTableHeaderTest();
};

ImportTableHeaderTest::~ImportTableHeaderTest() = default;

TEST_F(ImportTableHeaderTest, initialStateTwoColumn)
{
    const int column_count{2};
    ImportTableHeader header(column_count);

    EXPECT_EQ(header.columnCount(), column_count);
    EXPECT_EQ(header.rowCount(), ImportTableHeader::MAX);
    EXPECT_EQ(header.columnInfo().size(), column_count);

    // first column is by default represents Axis
    EXPECT_EQ(header.columnInfo()[0].column, 0);
    EXPECT_EQ(header.columnInfo()[0].type_name, Constants::AxisType);
    EXPECT_EQ(header.columnInfo()[0].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[0].multiplier, 1.0);
    EXPECT_EQ(header.columnInfo()[0].title, std::string(""));

    // second column is by default represents Intensity
    EXPECT_EQ(header.columnInfo()[1].column, 1);
    EXPECT_EQ(header.columnInfo()[1].type_name, Constants::IntensityType);
    EXPECT_EQ(header.columnInfo()[1].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[1].multiplier, 1.0);
    EXPECT_EQ(header.columnInfo()[1].title, std::string(""));
}

TEST_F(ImportTableHeaderTest, initialStateThreeColumn)
{
    const int column_count{3};
    ImportTableHeader header(column_count);

    EXPECT_EQ(header.columnCount(), column_count);
    EXPECT_EQ(header.rowCount(), ImportTableHeader::MAX);
    EXPECT_EQ(header.columnInfo().size(), column_count);

    // first column is by default represents Axis
    EXPECT_EQ(header.columnInfo()[0].column, 0);
    EXPECT_EQ(header.columnInfo()[0].type_name, Constants::AxisType);
    EXPECT_EQ(header.columnInfo()[0].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[0].multiplier, 1.0);
    EXPECT_EQ(header.columnInfo()[0].title, std::string(""));

    // second column is by default represents Intensity
    EXPECT_EQ(header.columnInfo()[1].column, 1);
    EXPECT_EQ(header.columnInfo()[1].type_name, Constants::IntensityType);
    EXPECT_EQ(header.columnInfo()[1].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[1].multiplier, 1.0);
    EXPECT_EQ(header.columnInfo()[1].title, std::string(""));

    // second column is by default represents Intensity
    EXPECT_EQ(header.columnInfo()[2].column, 2);
    EXPECT_EQ(header.columnInfo()[2].type_name, Constants::IntensityType);
    EXPECT_EQ(header.columnInfo()[2].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[2].multiplier, 1.0);
    EXPECT_EQ(header.columnInfo()[2].title, std::string(""));
}

TEST_F(ImportTableHeaderTest, rowName)
{
    const int column_count{2};
    ImportTableHeader header(column_count);

    EXPECT_EQ(header.rowName(0), "Type");
    EXPECT_EQ(header.rowName(1), "Unit");
    EXPECT_EQ(header.rowName(2), "Multiplier");
    EXPECT_EQ(header.rowName(3), "Name");
}

TEST_F(ImportTableHeaderTest, setData)
{
    const int column_count{2};
    ImportTableHeader header(column_count);

    EXPECT_EQ(header.columnCount(), column_count);
    EXPECT_EQ(header.rowCount(), ImportTableHeader::MAX);
    EXPECT_EQ(header.columnInfo().size(), column_count);

    const std::vector<std::string> typeNames = {Constants::AxisType, Constants::IntensityType,
                                                Constants::IgnoreType};
    auto combo = ModelView::ComboProperty::createFrom(typeNames);
    combo.setValue(Constants::IgnoreType);

    header.setData(ImportTableHeader::TYPE, 0, QVariant::fromValue(combo));
    header.setData(ImportTableHeader::MULTIPLIER, 0, QVariant::fromValue(2.0));
    header.setData(ImportTableHeader::TITLE, 0, QVariant::fromValue(QString("abc")));

    // first column is by default represents Axis
    EXPECT_EQ(header.columnInfo()[0].column, 0);
    EXPECT_EQ(header.columnInfo()[0].type_name, Constants::IgnoreType);
    EXPECT_EQ(header.columnInfo()[0].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[0].multiplier, 2.0);
    EXPECT_EQ(header.columnInfo()[0].title, std::string("abc"));

    // second column is by default represents Intensity
    EXPECT_EQ(header.columnInfo()[1].column, 1);
    EXPECT_EQ(header.columnInfo()[1].type_name, Constants::IntensityType);
    EXPECT_EQ(header.columnInfo()[1].units, std::string("a.u."));
    EXPECT_EQ(header.columnInfo()[1].multiplier, 1.0);
    EXPECT_EQ(header.columnInfo()[1].title, std::string(""));
}
