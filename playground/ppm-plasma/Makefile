CXX      = clang++
CXXFLAGS = -std=c++23 -O3 -Wall
LDLIBS   = -lm
SRC      = plasma.cpp
TARGET   = plasma

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

run: build
	./$(TARGET)
	ffmpeg -y -framerate 60 -i assets/output-%03d.ppm -pix_fmt yuv420p output.mp4
	ffmpeg -y -i output.mp4 -vf "fps=30,scale=480:-1:flags=lanczos,split[a][b];[a]palettegen[p];[b][p]paletteuse" output.gif
	xdg-open output.mp4

clean:
	rm -rf $(TARGET) assets output.mp4
