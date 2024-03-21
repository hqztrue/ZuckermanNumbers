#!/bin/bash
set -x #echo on

T=60

timeout $T ./Zuckerman 3 > Zuckerman3.output
timeout $T ./Zuckerman 4 > Zuckerman4.output
timeout $T ./Zuckerman 5 > Zuckerman5.output
timeout $T ./Zuckerman 6 > Zuckerman6.output
timeout $T ./Zuckerman 7 > Zuckerman7.output
timeout $T ./Zuckerman 8 > Zuckerman8.output
timeout $T ./Zuckerman 9 > Zuckerman9.output
timeout $T ./Zuckerman 10 > Zuckerman10.output
timeout $T ./Zuckerman 11 > Zuckerman11.output
timeout $T ./Zuckerman 12 > Zuckerman12.output
