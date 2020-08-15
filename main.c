#include "core.h"
#include "locale.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    waitRequest();
    return 0;
}
