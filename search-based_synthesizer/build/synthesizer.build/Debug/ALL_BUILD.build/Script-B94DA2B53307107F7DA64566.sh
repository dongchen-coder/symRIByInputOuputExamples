#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  echo Build\ all\ projects
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/dchen/tools/symRiSynthesizer/symRIByInputOuputExamples/synthesizer/build
  echo Build\ all\ projects
fi

