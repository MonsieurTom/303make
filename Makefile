NAME = 		303make

RM	=	rm -f

CC	=	g++

SRCS	=	main.cpp \
		FileReader.cpp \
		DataExtractor.cpp 

OBJS	=	$(SRCS:.cpp=.o)

CPPFLAGS	+= -W -Wall -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
