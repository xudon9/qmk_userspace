// clang-format off

#define LAYOUT_LR_THUMB(                \
    k00, k01, k02, k03, k04, k05, k06,  \
    k10, k11, k12, k13, k14, k15, k16,  \
    k20, k21, k22, k23, k24, k25,       \
                                        \
    k46, k45, k44, k43, k42, k41, k40,  \
    k56, k55, k54, k53, k52, k51, k50,  \
         k65, k64, k63, k62, k61, k60,  \
    k33, k34, k35,       k75, k74, k73) \
         LAYOUT_split_3x6_3_ex2(        \
    k00, k01, k02, k03, k04, k05, k06, k46, k45, k44, k43, k42, k41, k40, \
    k10, k11, k12, k13, k14, k15, k16, k56, k55, k54, k53, k52, k51, k50, \
    k20, k21, k22, k23, k24, k25,           k65, k64, k63, k62, k61, k60, \
                   k33, k34, k35,           k75, k74, k73)
// clang-format on

// Matrix positions of the left hand home row keys.
#define LEFT_HOME_ROW           1
#define LEFT_HOME_PINKY_COL     1
#define LEFT_HOME_RING_COL      2
#define LEFT_HOME_MIDDLE_COL    3
#define LEFT_HOME_INDEX_COL     4
