#ifndef __colors__
#define __colors__ = 1

#define GREEN "\033[38;5;114m"
#define BLUE "\033[38;5;69m"  // Color Start
#define RED "\033[38;5;203m"  // Color Start
#define RED_BACK "\033[48;5;210m"

#define COLOR_END "\033[0m"  // To flush out prev settings
#define log_green(X) printf("%s%s%s\n", GREEN, X, COLOR_END)
#define green(X) sprintf("%s%s%s", GREEN, X, COLOR_END)

#define log_blue(X) printf("%s%s%s", BLUE, X, COLOR_END)
#define log_red(X) printf("%s%s%s\n", RED, X, COLOR_END)
#define warning(X) printf("%s %s %s\n", RED_BACK, X, COLOR_END)

#endif