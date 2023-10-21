NAME=ChPong
SRCS=$(wildcard srcs/*)
OBJS=$(subst srcs,objs,$(subst .cpp,.o,$(SRCS)))
INCLUDES=includes
FLAGS=-lsfml-window -lsfml-system -lsfml-graphics -I includes

$(NAME): build $(OBJS)
	g++ $(OBJS) -o $(NAME) $(FLAGS)

$(OBJS): objs/%.o: srcs/%.cpp
	g++ -c $< -o $@ $(FLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

build:
	@mkdir -p objs

debug:
	g++ $(SRCS) -o "$(NAME)_debug" $(FLAGS) -g
