/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-12-07 15:08
 * Last modified : 2020-12-07 15:08
 * Filename      : locate.c
 * Description   :
 *********************************************************************/
#include <iostream>
#include <math.h> // sqrt fabs
#include <stdio.h>

// 点
struct point_t {
  double x, y;
};

// 圆
struct circle_t {
  struct point_t center;
  double r;
};

// 浮点数判同
int double_equals(double const a, double const b) {
  static const double ZERO = 1e-9;
  return fabs(a - b) < ZERO;
}

// 两点之间距离的平方
double distance_sqr(struct point_t const *a, struct point_t const *b) {
  return (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y);
}

// 两点之间的距离
double distance(struct point_t const *a, struct point_t const *b) {
  return sqrt(distance_sqr(a, b));
}

/*
 * 两圆相交函数
 * 参数:
 *    circles[0] 和 circles[1] 分别是两个圆.
 *    points[0] 和 points[1] 用来存放交点数值, 虽然有些情况下两个不都会用上;
 *        如果用到了两个交点, 那么返回后, 横坐标大的在前, 如果横坐标一样,
 * 则纵坐标大的在前. 返回值: -1 如果两个圆一模一样; 其它整数值: 交点个数.
 */
int insect(struct circle_t circles[], struct point_t points[]) {
  double d, a, b, c, p, q, r; // a, b, c, p, q, r 与上面分析中的量一致
  double cos_value[2], sin_value[2]; // 交点的在 circles[0] 上对应的正余弦取值
                                     // 余弦值 cos_value 就是分析中的 cosθ
  if (double_equals(circles[0].center.x, circles[1].center.x) &&
      double_equals(circles[0].center.y, circles[1].center.y) &&
      double_equals(circles[0].r, circles[1].r)) {
    return -1;
  }

  d = distance(&circles[0].center, &circles[1].center); // 圆心距离
  if (d > circles[0].r + circles[1].r ||
      d < fabs(circles[0].r - circles[1].r)) {
    return 0;
  }

  a = 2.0 * circles[0].r * (circles[0].center.x - circles[1].center.x);
  b = 2.0 * circles[0].r * (circles[0].center.y - circles[1].center.y);
  c = circles[1].r * circles[1].r - circles[0].r * circles[0].r -
      distance_sqr(&circles[0].center, &circles[1].center);
  p = a * a + b * b;
  q = -2.0 * a * c;

  // 如果交点仅一个
  if (double_equals(d, circles[0].r + circles[1].r) ||
      double_equals(d, fabs(circles[0].r - circles[1].r))) {
    cos_value[0] = -q / p / 2.0;
    sin_value[0] = sqrt(1 - cos_value[0] * cos_value[0]);

    points[0].x = circles[0].r * cos_value[0] + circles[0].center.x;
    points[0].y = circles[0].r * sin_value[0] + circles[0].center.y;

    // 在这里验证解是否正确, 如果不正确, 则将纵坐标符号进行变换
    if (!double_equals(distance_sqr(&points[0], &circles[1].center),
                       circles[1].r * circles[1].r)) {
      points[0].y = circles[0].center.y - circles[0].r * sin_value[0];
    }
    return 1;
  }

  r = c * c - b * b;
  cos_value[0] = (sqrt(q * q - 4.0 * p * r) - q) / p / 2.0;
  cos_value[1] = (-sqrt(q * q - 4.0 * p * r) - q) / p / 2.0;
  sin_value[0] = sqrt(1 - cos_value[0] * cos_value[0]);
  sin_value[1] = sqrt(1 - cos_value[1] * cos_value[1]);

  points[0].x = circles[0].r * cos_value[0] + circles[0].center.x;
  points[1].x = circles[0].r * cos_value[1] + circles[0].center.x;
  points[0].y = circles[0].r * sin_value[0] + circles[0].center.y;
  points[1].y = -(circles[0].r * sin_value[1]) + circles[0].center.y;

  // 验证解是否正确, 两个解都需要验证.
  // if (!double_equals(distance_sqr(&points[0], &circles[1].center),
  // circles[1].r * circles[1].r)) {
  // points[0].y = circles[0].center.y - circles[0].r * sin_value[0];
  // }
  // if (!double_equals(distance_sqr(&points[1], &circles[1].center),
  // circles[1].r * circles[1].r)) {
  // points[1].y = circles[0].center.y - circles[0].r * sin_value[1];
  // }
  // 如果求得的两个点坐标相同, 则必然其中一个点的纵坐标反号可以求得另一点坐标
  // if (double_equals(points[0].y, points[1].y) &&
  // double_equals(points[0].x, points[1].x)) {
  // if (points[0].y > 0) {
  // points[1].y = -points[1].y;
  // } else {
  // points[0].y = -points[0].y;
  // }
  // }
  return 2;
}

struct circle_t *select_appropriate_circle(struct circle_t circle_ab[2],
                                           struct circle_t circle_cd[2]) {
  if (circle_ab[0].r < circle_cd[0].r && circle_ab[1].r < circle_cd[1].r) {
    return circle_ab;
  }
  if (circle_ab[0].r > circle_cd[0].r && circle_ab[1].r > circle_cd[1].r) {
    return circle_cd;
  }
  if (circle_ab[0].r < circle_cd[0].r && circle_ab[1].r < circle_cd[1].r) {
    return circle_cd;
  }
  if (circle_ab[0].r < circle_cd[0].r && circle_ab[1].r < circle_cd[1].r) {
    return circle_cd;
  }
  return (struct circle_t *)(0);
}

double check_circle_insect(struct circle_t circle[2], struct point_t point[2]) {
  double r0 =
      (point[0].x - circle[0].center.x) * (point[0].x - circle[0].center.x) +
      (point[0].y - circle[0].center.y) * (point[0].y - circle[0].center.y);
  double delta_r0 = fabs(r0 - circle[0].r * circle[0].r);
  double r1 =
      (point[1].x - circle[1].center.x) * (point[1].x - circle[1].center.x) +
      (point[1].y - circle[1].center.y) * (point[1].y - circle[1].center.y);
  double delta_r1 = fabs(r1 - circle[1].r * circle[1].r);
  double delta = delta_r0 - delta_r1;
  return delta;
}

int select_appropriate_point(struct circle_t circle_ab[2],
                             struct circle_t circle_cd[2],
                             struct point_t point[2]) {
  double delta = 1.0;
  if (circle_ab[0].r < circle_cd[0].r && circle_ab[1].r < circle_cd[1].r) {
    delta = check_circle_insect(circle_cd, point);
    std::cout << "cd " << delta << std::endl;
    return (delta > 0) ? 1 : 0;
  }
  if (circle_ab[0].r > circle_cd[0].r && circle_ab[1].r > circle_cd[1].r) {
    delta = check_circle_insect(circle_ab, point);
    std::cout << "ab " << delta << std::endl;
    return (delta > 0) ? 1 : 0;
  }
  return delta;
}

int get_appropriate_point(struct circle_t circle_ab[2],
                          struct circle_t circle_cd[2],
                          struct point_t point[2]) {
  if (circle_ab[0].r < circle_cd[0].r && circle_ab[1].r < circle_cd[1].r) {
    if (point[0].y > 0)
      return 0;
    if (point[1].y > 0)
      return 1;
  }
  if (circle_ab[0].r > circle_cd[0].r && circle_ab[1].r > circle_cd[1].r) {
    if (point[0].y < 0)
      return 0;
    if (point[1].y < 0)
      return 1;
  }
  return 0;
}

void distance_rectify(double *r1, double *r2, double d) {
  if (r1 == NULL)
    return;
  if (r2 == NULL)
    return;
  double a = *r1;
  double b = *r2;
  if ((a + b > d) && (fabs(a - b) < d)) {
    return;
  }
  if ((a + b < d) && (fabs(a - b) < d)) {
    return;
  }
  if ((a + b > d) && (fabs(a - b) > d)) {
    return;
  }
  if ((a + b < d) && (fabs(a - b) < d)) {
    return;
  }
}

struct point_t get_object_position(struct circle_t circle_ab[2],
                                   struct circle_t circle_cd[2]) {
  struct circle_t *circle;
  struct point_t point[2];
  struct point_t p;
  int distance_ab = distance_sqr(&circle_ab[0].center, &circle_ab[0].center);
  int distance_cd = distance_sqr(&circle_cd[0].center, &circle_cd[0].center);
  // 锚点a ,b和目标组成一个三角形, 根据三角形两边之和大于第三边,
  // 两边之差小于第三边 对锚点到目标的距离进行适当矫正
  distance_rectify(&circle_ab[0].r, &circle_ab[1].r, distance_ab);
  distance_rectify(&circle_cd[0].r, &circle_cd[1].r, distance_cd);
  //根据目标到各组锚点的距离最小选择那组锚点参与坐标计算
  circle = select_appropriate_circle(circle_ab, circle_cd);

  switch (insect(circle, point)) {
  case -1:
    //需要矫正
    p.x = circle[0].r + circle[0].center.x +
          fabs(circle[1].center.x - circle[0].center.x) / 2;
    p.y = circle[0].center.y;
    break;
  case 0:
    //需要矫正
    p.x = circle[0].r + circle[0].center.x +
          fabs(circle[1].center.x - circle[0].center.x) / 2;
    p.y = circle[0].center.y;
    break;
  case 1:
    p.x = point[0].x;
    p.y = point[0].y;
    break;
  case 2:
    // 方案1: 根据目标坐标的y位置的正负选择正确的目标位置,
    // 与选择的坐标西有关系 int index = get_appropriate_point(circle_ab,
    // circle_cd, point); 方案2:
    // 根据目标到各组锚点的距离选择那组锚点参与坐标验证
    int index = select_appropriate_point(circle_ab, circle_cd, point);
    p.x = point[index].x;
    p.y = point[index].y;
  }
  return p;
}

//将锚点分组, a,b锚点为一组,
// c,d,为一组,根据目标到锚点到目标的距离,以及两锚点的坐标, 求解目标的坐标(x,
// y),
//可以建模成求解两为圆的交点的数学模型
int main(int argc, char **argv) {
  struct circle_t circle_ab[2];
  struct circle_t circle_cd[2];
  struct point_t point;
  while (1) {
    printf("请输入锚点a和锚点b的坐标及目标距a,b的距离d0和d1(各输入值以逗号分开)"
           "：");
    scanf("%lf,%lf,%lf,%lf,%lf,%lf", &circle_ab[0].center.x,
          &circle_ab[0].center.y, &circle_ab[0].r, &circle_ab[1].center.x,
          &circle_ab[1].center.y, &circle_ab[1].r);
    printf("请输入锚点c和锚地d的坐标及目标距c,d的距离d2和d3(各输入值以逗号分开)"
           "：");
    scanf("%lf,%lf,%lf,%lf,%lf,%lf", &circle_cd[0].center.x,
          &circle_cd[0].center.y, &circle_cd[0].r, &circle_cd[1].center.x,
          &circle_cd[1].center.y, &circle_cd[1].r);

    point = get_object_position(circle_ab, circle_cd);
    printf("(The real position is: %.3lf %.3lf\n)", point.x, point.y);
  }
  return 0;
}
