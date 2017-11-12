#include <TRecordReader.hxx>
#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>

const auto fname = "small.raw";

struct with_width {
   int w;
   with_width(int w) : w(w) {}
};
auto operator<<(std::ostream &os, const with_width &w) -> decltype(os << std::setw(0) << std::left)
{
   return os << std::setw(w.w) << std::left;
}

TEST(RecordReader, TraverseRecords)
{
   TRecordReader r(fname);
   for (auto recordn = 0u; r.NextRecord(); ++recordn)
      std::cout << "record " << with_width(7) << recordn << " pos: " << with_width(10) << r.GetRecordPosition()
                << " size: " << with_width(7) << r.GetRecordSize() << '\n';
}

TEST(RecordReader, TraverseBanks)
{
   TRecordReader r(fname);
   for (auto recordn = 0u; r.NextRecord(); ++recordn) {
      std::cout << "record " << with_width(7) << recordn << '\n';
      for (auto bankn = 0u; r.NextBank(); ++bankn) {
         auto bankHeader = r.GetBankHeader();
         std::cout << "    bank " << with_width(7) << bankn << " pos: " << with_width(10) << r.GetBankPosition()
                   << " size: " << with_width(7) << bankHeader.size << " type: " << with_width(7) << bankHeader.type
                   << " version: " << with_width(7) << bankHeader.version << '\n';
      }
   }
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
