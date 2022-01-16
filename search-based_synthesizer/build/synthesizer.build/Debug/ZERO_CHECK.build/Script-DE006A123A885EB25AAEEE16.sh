#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  make -f /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  make -f /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  make -f /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  make -f /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build/CMakeScripts/ReRunCMake.make
fi

