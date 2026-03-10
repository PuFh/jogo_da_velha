CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp Tabuleiro.cpp Jogador.cpp JogadorHumano.cpp \
       BotAleatorio.cpp BotTatico.cpp MotorJogo.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = jogo_da_velha

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
