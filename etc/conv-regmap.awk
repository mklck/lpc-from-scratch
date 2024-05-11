
BEGIN {
	if (ARGV[1] == "linker" || ARGV[1] == "header")
		type = ARGV[1]
	else if (ARGV[1] != "") {
		printf "usage: %s [linker | header]\n", ARGV[0]
		exit 1
	} else {
		type = "linker"
	}

	ARGV[1] = ""

	if (type == "header")
		print "#include \"u.h\"\n"
}

# empty lines and comments
/^(#.*)?$/ {next}

// {
	if (type == "linker")
		printf "%s = %s;\n", $1, $2
	else
		printf "extern Port %s;\n", $1
}