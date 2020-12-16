#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

void help(char **argv) {
  cout << "\nThis program demosrates iterative construction of\n"
          "delanunay triangulation and voronoi tessellation.\n"
          "It draw a random set of points in an image and then delaunay "
          "triangulates them."
          "Usage: \n";
  cout << argv[0];
  cout << "\n\nThis program builds the triangulation interactively, "
          "you may stop this proces by\n hitting any key.\n";
}

static void draw_subdiv_point(cv::Mat &img, cv::Point2f fp, cv::Scalar color) {
  cv::circle(img, fp, 3, color, cv::FILLED, cv::LINE_8, 0);
}

static void draw_subdiv(cv::Mat &img, cv::Subdiv2D subdiv,
                        cv::Scalar delaunay_color) {
  std::vector<cv::Vec6f> triangleList;
  subdiv.getTriangleList(triangleList);
  std::vector<Point> pt(3);
  for (size_t i = 0; i < triangleList.size(); i++) {
    cv::Vec6f t = triangleList[i];
    pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
    pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
    pt[2] = Point(cvRound(t[4]), cvRound(t[5]));
    line(img, pt[0], pt[1], delaunay_color, 1, cv::LINE_AA, 0);
    line(img, pt[0], pt[1], delaunay_color, 1, cv::LINE_AA, 0);
    line(img, pt[2], pt[0], delaunay_color, 1, LINE_AA, 0);
  }
}

static void locate_point(cv::Mat &img, cv::Subdiv2D &subdiv, cv::Point2f fp,
                         cv::Scalar active_color) {
  int e0 = 0, vertex = 0;
  subdiv.locate(fp, e0, vertex);
  if (e0 > 0) {
    int e = e0;
    do {
      cv::Point2f org, dst;
      if (subdiv.edgeOrg(e, &org) > 0 && subdiv.edgeDst(e, &dst)) {
        line(img, org, dst, active_color, 3, LINE_AA, 0);
        e = subdiv.getEdge(e, Subdiv2D::NEXT_AROUND_LEFT);
      }
    } while (e != e0);
    draw_subdiv_point(img, fp, active_color);
  }
}

static void paint_voronoi(cv::Mat &img, cv::Subdiv2D subdiv) {
  vector<vector<Point2f>> facets;
  vector<Point2f> centers;
  subdiv.getVoronoiFacetList(vector<int>(), facets, centers);
  vector<Point> ifacet;
  vector<vector<Point>> ifacets(1);
  for (size_t i = 0; i < facets.size(); i++) {
    ifacet.resize(facets[i].size());
    for (size_t j = 0; j < facets[i].size(); j++) {
      ifacet[j] = facets[i][j];
    }
    cv::Scalar color;
    color[0] = rand()&255;
    color[1] = rand()&255;
    color[2] = rand()&255;
    fillConvexPoly(img, ifacet, color, 8, 0);
    ifacets[0]= ifacet;
    polylines(img, ifacets, true, cv::Scalar(), 1, LINE_AA, 0);
    circle(img, centers[i], 3, Scalar(), FILLED, LINE_AA);
  }
}

int main(int argc, char **argv) {
  cv::CommandLineParser parser(argc, argv, "{help h||}");
  if (parser.has("help")) {
    help(argv);
    return 0;
  }
  Scalar active_facet_color(0, 0, 255);
  Scalar delaunay_color(255, 255, 255);
  cv::Rect rect(0, 0, 600, 600);
  Subdiv2D subdiv(rect);
  cv::Mat img(rect.size(), CV_8UC3);
  img = cv::Scalar::all(0);
  std::string win = "Delaunay Demo";
  cv::imshow(win, img);
  for (int i = 0; i < 200; i++) {
    cv::Point2f fp((float)(rand() % (rect.width - 10) + 5),
                   (float)(rand() % (rect.height - 10) + 5));
    locate_point(img, subdiv, fp, active_facet_color);
    cv::imshow(win, img);
    if (cv::waitKey(100) >= 0)
      break;
    subdiv.insert(fp);
    img = Scalar::all(0);
    draw_subdiv(img, subdiv, delaunay_color);
    cv::imshow(win, img);
    if (cv::waitKey(100) >= 0)
      break;
  }
  img = cv::Scalar::all(0);
  paint_voronoi(img, subdiv);
  cv::imshow(win, img);
  cv::waitKey(0);
  return 0;
}
