FLAGS = -D_DEBUG -ggdb3 -std=c++17 -O0 \
  -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat \
  -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
  -Wconditionally-supported -Wconversion -Wctor-dtor-privacy \
  -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
  -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
  -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked \
  -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow \
  -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
  -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
  -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef \
  -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
  -Wno-literal-suffix -Wno-missing-field-initializers \
  -Wno-narrowing -Wno-old-style-cast -Wno-varargs \
  -fcheck-new -fsized-deallocation -fstack-protector \
  -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
  -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
  -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

OBJDIR = obj

solve: $(OBJDIR)/main.o $(OBJDIR)/input.o $(OBJDIR)/output.o $(OBJDIR)/solver.o \
    $(OBJDIR)/parameters.o $(OBJDIR)/tests.o $(OBJDIR)/utils.o $(OBJDIR)/arts.o
	@g++ $(OBJDIR)/main.o $(OBJDIR)/input.o $(OBJDIR)/output.o $(OBJDIR)/solver.o \
    $(OBJDIR)/parameters.o $(OBJDIR)/tests.o $(OBJDIR)/utils.o $(OBJDIR)/arts.o $(FLAGS) -o solve

$(OBJDIR)/main.o: main.cpp
	@g++ -c main.cpp $(FLAGS) -o $(OBJDIR)/main.o

$(OBJDIR)/input.o: input.cpp
	@g++ -c input.cpp $(FLAGS) -o $(OBJDIR)/input.o

$(OBJDIR)/output.o: output.cpp
	@g++ -c output.cpp $(FLAGS) -o $(OBJDIR)/output.o

$(OBJDIR)/solver.o: solver.cpp
	@g++ -c solver.cpp $(FLAGS) -o $(OBJDIR)/solver.o

$(OBJDIR)/parameters.o: parameters.cpp
	@g++ -c parameters.cpp $(FLAGS) -o $(OBJDIR)/parameters.o

$(OBJDIR)/tests.o: tests.cpp
	@g++ -c tests.cpp $(FLAGS) -o $(OBJDIR)/tests.o

$(OBJDIR)/utils.o: utils.cpp
	@g++ -c utils.cpp $(FLAGS) -o $(OBJDIR)/utils.o

$(OBJDIR)/arts.o: arts.cpp
	@g++ -c arts.cpp $(FLAGS) -o $(OBJDIR)/arts.o



