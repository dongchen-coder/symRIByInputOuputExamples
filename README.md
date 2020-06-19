# Symbolic Reuse Interval Synthesizer By Inputoutput Examples

This project is trying to explore synthesizing symbolic reuse interval expressions with inputoutput examples.

Current issues and TODOs:

(1) ~~Basic bottom-up search does not scale (which is expected). Need to support unification described in "synthesis through unification" or divide and conquer in "scaling enumerative program synthesis via divide and conquer"~~

(2) ~~Need to make language definition support seperating "predicts" and "terms"~~

(3) ~~Need to add time bound for search() in bottom-up and unification search.~~

(4) ~~extand corrent language definition to support left and right shift operation~~

(5) ~~When grow, commutative expressions only generate once~~

Questions:

(1) Is there any specification that can be used to guide the search?

(2) How to ensure progress?

(3) Rules to remove equalivents? (1) Type guided: contant > var > expr (2) length guided: short > long (3) random? (4) reserve more than one? 
