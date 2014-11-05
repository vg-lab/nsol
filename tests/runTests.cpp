

#include <limits.h>
#include <gtest/gtest.h>

#include "NodeTest.h"
#include "SegmentTest.h"
#include "SectionTest.h"
#include "NeuriteTest.h"
#include "DendriteTest.h"
#include "AxonTest.h"
#include "SomaTest.h"
#include "NeuronMorphologyTest.h"
#include "NeuronTest.h"
#include "MiniColumnTest.h"
#include "ColumnTest.h"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
