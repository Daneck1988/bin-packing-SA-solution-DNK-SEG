# Flag para alterar o padrão do compilador
standart = -std=c++17

# Flags para otimizar o arquivo executável
optimize_flags = -O3 -pipe -flto

# Flags para ativar todos os avisos do compilador
warnings = -Wall -Wextra -Werror -Wformat=2 -Wno-maybe-uninitialized \
	   -Wformat-overflow=2 -Wundef -Wconversion -Wwrite-strings

# Flags para depurar o código
sanitize = -fsanitize=address,undefined,pointer-compare,pointer-subtract
debug_flags = -ggdb3 -Og -DDEBUG -Wformat-truncation=2 $(sanitize)

CC := /usr/bin/gcc
CXX := /usr/bin/g++

builddir := build
objectname = sabp
objectdir = $(builddir)/$(objectname)

.PHONY: all debug

all:set_flags $(objectdir)

debug:set_debug_flags $(objectdir)

$(objectdir):$(builddir) $(builddir)/random.o $(builddir)/sa.o src/main.cpp
	$(CXX) $(CPPFLAGS) $(builddir)/random.o $(builddir)/sa.o src/main.cpp -o $(objectdir)

$(builddir)/random.o:src/random.cpp
	$(CXX) $(CPPFLAGS) src/random.cpp -o $(builddir)/random.o -c

$(builddir)/sa.o:src/sa.cpp
	$(CXX) $(CPPFLAGS) src/sa.cpp -o $(builddir)/sa.o -c

$(builddir):
	mkdir -p $(builddir)

set_flags:
	$(eval override CPPFLAGS += $(warnings) $(optimize_flags) $(standart))

set_debug_flags:
	$(eval override CPPFLAGS += $(warnings) $(sanitize) $(debug_flags))

clean:
	rm -rf $(builddir)
