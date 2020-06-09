#ifndef PLAY_UI_H_
#define PLAY_UI_H_
/* 剧目类型定义 */
typedef enum {
    PLAY_TYPE_FILM = 1,
    PLAY_TYPE_OPEAR = 2,
    PLAY_TYPE_CONCERT = 3,
}play_type_t;

/* 剧目分级类型定义 */
typedef enum {
    PLAY_TYPE_CHILD = 1,
    PLAY_RATE_TEENAGE = 2,
    PLAY_RATE_ADULT = 3
}play_rating_t;

/* 日期类型的定义如下 */
typedef struct {
    int year；
    int month;
    int day;
}
#endif