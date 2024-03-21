
CXX=g++
CXXFLAGS=-fopenmp -Ofast

Zuckerman: Zuckerman.cpp Zuckerman.sbatch
	$(CXX) $< -o Zuckerman $(CXXFLAGS)
	./create_sbatch.sh
									
all: Zuckerman

clean:
	rm -f Zuckerman
	rm -f Zuckerman3.sbatch
	rm -f Zuckerman4.sbatch
	rm -f Zuckerman5.sbatch
	rm -f Zuckerman6.sbatch
	rm -f Zuckerman7.sbatch
	rm -f Zuckerman8.sbatch
	rm -f Zuckerman9.sbatch
	rm -f Zuckerman10.sbatch
	rm -f Zuckerman11.sbatch
	rm -f Zuckerman12.sbatch
