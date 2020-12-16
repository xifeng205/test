/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-10-04 10:05
 * Last modified : 2020-10-04 10:05
 * Filename      : find_int_argc.c
 * Description   :
 *********************************************************************/
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#define SECRET_NUM -1234

typedef struct {
  int rows, cols;
  float **vals;
} matrix;

typedef struct {
  float x, y, w, h;
} box;
typedef struct {
  int w, h;
  matrix X;
  matrix y;
  int shallow;
  int *num_boxes;
  box **boxes;
} data;
typedef struct node {
  void *val;
  struct node *next;
  struct node *prev;
} node;

typedef struct list {
  int size;
  node *front;
  node *back;
} list;

typedef struct {
  char *type;
  list *options;
} section;

typedef enum {
  CONVOLUTIONAL,
  DECONVOLUTIONAL,
  CONNECTED,
  MAXPOOL,
  SOFTMAX,
  DETECTION,
  DROPOUT,
  CROP,
  ROUTE,
  COST,
  NORMALIZATION,
  AVGPOOL,
  LOCAL,
  SHORTCUT,
  ACTIVE,
  RNN,
  GRU,
  LSTM,
  CRNN,
  BATCHNORM,
  NETWORK,
  XNOR,
  REGION,
  YOLO,
  ISEG,
  REORG,
  UPSAMPLE,
  LOGXENT,
  L2NORM,
  BLANK
} LAYER_TYPE;

struct network;
typedef struct network network;

struct layer;
typedef struct layer layer;

typedef enum { SSE, MASKED, L1, SEG, SMOOTH, WGAN } COST_TYPE;
typedef enum {
  LOGISTIC,
  RELU,
  RELIE,
  LINEAR,
  RAMP,
  TANH,
  PLSE,
  LEAKY,
  ELU,
  LOGGY,
  STAIR,
  HARDTAN,
  LHTAN,
  SELU
} ACTIVATION;

typedef struct {
  int batch;
  float learning_rate;
  float momentum;
  float decay;
  int adam;
  float B1;
  float B2;
  float eps;
  int t;
} update_args;

typedef struct {
  int *leaf;
  int n;
  int *parent;
  int *child;
  int *group;
  char **name;
  int groups;
  int *group_size;
  int *group_offset;
} tree;

struct layer {
  LAYER_TYPE type;
  ACTIVATION activation;
  COST_TYPE cost_type;
  void (*forward)(struct layer, struct network);
  void (*backward)(struct layer, struct network);
  void (*update)(struct layer, update_args);
  void (*forward_gpu)(struct layer, struct network);
  void (*backward_gpu)(struct layer, struct network);
  void (*update_gpu)(struct layer, update_args);
  int batch_normalize;
  int shortcut;
  int batch;
  int forced;
  int flipped;
  int inputs;
  int outputs;
  int nweights;
  int nbiases;
  int extra;
  int truths;
  int h, w, c;
  int out_h, out_w, out_c;
  int n;
  int max_boxes;
  int groups;
  int size;
  int side;
  int stride;
  int reverse;
  int flatten;
  int spatial;
  int pad;
  int sqrt;
  int flip;
  int index;
  int binary;
  int xnor;
  int steps;
  int hidden;
  int truth;
  float smooth;
  float dot;
  float angle;
  float jitter;
  float saturation;
  float exposure;
  float shift;
  float ratio;
  float learning_rate_scale;
  float clip;
  int noloss;
  int softmax;
  int classes;
  int coords;
  int background;
  int rescore;
  int objectness;
  int joint;
  int noadjust;
  int reorg;
  int log;
  int tanh;
  int *mask;
  int total;

  float alpha;
  float beta;
  float kappa;

  float coord_scale;
  float object_scale;
  float noobject_scale;
  float mask_scale;
  float class_scale;
  int bias_match;
  int random;
  float ignore_thresh;
  float truth_thresh;
  float thresh;
  float focus;
  int classfix;
  int absolute;

  int onlyforward;
  int stopbackward;
  int dontload;
  int dontsave;
  int dontloadscales;
  int numload;

  float temperature;
  float probability;
  float scale;

  char *cweights;
  int *indexes;
  int *input_layers;
  int *input_sizes;
  int *map;
  int *counts;
  float **sums;
  float *rand;
  float *cost;
  float *state;
  float *prev_state;
  float *forgot_state;
  float *forgot_delta;
  float *state_delta;
  float *combine_cpu;
  float *combine_delta_cpu;

  float *concat;
  float *concat_delta;

  float *binary_weights;

  float *biases;
  float *bias_updates;

  float *scales;
  float *scale_updates;

  float *weights;
  float *weight_updates;

  float *delta;
  float *output;
  float *loss;
  float *squared;
  float *norms;

  float *spatial_mean;
  float *mean;
  float *variance;

  float *mean_delta;
  float *variance_delta;

  float *rolling_mean;
  float *rolling_variance;

  float *x;
  float *x_norm;

  float *m;
  float *v;

  float *bias_m;
  float *bias_v;
  float *scale_m;
  float *scale_v;

  float *z_cpu;
  float *r_cpu;
  float *h_cpu;
  float *prev_state_cpu;

  float *temp_cpu;
  float *temp2_cpu;
  float *temp3_cpu;

  float *dh_cpu;
  float *hh_cpu;
  float *prev_cell_cpu;
  float *cell_cpu;
  float *f_cpu;
  float *i_cpu;
  float *g_cpu;
  float *o_cpu;
  float *c_cpu;
  float *dc_cpu;

  float *binary_input;

  struct layer *input_layer;
  struct layer *self_layer;
  struct layer *output_layer;

  struct layer *reset_layer;
  struct layer *update_layer;
  struct layer *state_layer;

  struct layer *input_gate_layer;
  struct layer *state_gate_layer;
  struct layer *input_save_layer;
  struct layer *state_save_layer;
  struct layer *input_state_layer;
  struct layer *state_state_layer;

  struct layer *input_z_layer;
  struct layer *state_z_layer;

  struct layer *input_r_layer;
  struct layer *state_r_layer;

  struct layer *input_h_layer;
  struct layer *state_h_layer;

  struct layer *wz;
  struct layer *uz;
  struct layer *wr;
  struct layer *ur;
  struct layer *wh;
  struct layer *uh;
  struct layer *uo;
  struct layer *wo;
  struct layer *uf;
  struct layer *wf;
  struct layer *ui;
  struct layer *wi;
  struct layer *ug;
  struct layer *wg;

  tree *softmax_tree;

  size_t workspace_size;

#ifdef GPU
  int *indexes_gpu;

  float *z_gpu;
  float *r_gpu;
  float *h_gpu;

  float *temp_gpu;
  float *temp2_gpu;
  float *temp3_gpu;

  float *dh_gpu;
  float *hh_gpu;
  float *prev_cell_gpu;
  float *cell_gpu;
  float *f_gpu;
  float *i_gpu;
  float *g_gpu;
  float *o_gpu;
  float *c_gpu;
  float *dc_gpu;

  float *m_gpu;
  float *v_gpu;
  float *bias_m_gpu;
  float *scale_m_gpu;
  float *bias_v_gpu;
  float *scale_v_gpu;

  float *combine_gpu;
  float *combine_delta_gpu;

  float *prev_state_gpu;
  float *forgot_state_gpu;
  float *forgot_delta_gpu;
  float *state_gpu;
  float *state_delta_gpu;
  float *gate_gpu;
  float *gate_delta_gpu;
  float *save_gpu;
  float *save_delta_gpu;
  float *concat_gpu;
  float *concat_delta_gpu;

  float *binary_input_gpu;
  float *binary_weights_gpu;

  float *mean_gpu;
  float *variance_gpu;

  float *rolling_mean_gpu;
  float *rolling_variance_gpu;

  float *variance_delta_gpu;
  float *mean_delta_gpu;

  float *x_gpu;
  float *x_norm_gpu;
  float *weights_gpu;
  float *weight_updates_gpu;
  float *weight_change_gpu;

  float *biases_gpu;
  float *bias_updates_gpu;
  float *bias_change_gpu;

  float *scales_gpu;
  float *scale_updates_gpu;
  float *scale_change_gpu;

  float *output_gpu;
  float *loss_gpu;
  float *delta_gpu;
  float *rand_gpu;
  float *squared_gpu;
  float *norms_gpu;
#ifdef CUDNN
  cudnnTensorDescriptor_t srcTensorDesc, dstTensorDesc;
  cudnnTensorDescriptor_t dsrcTensorDesc, ddstTensorDesc;
  cudnnTensorDescriptor_t normTensorDesc;
  cudnnFilterDescriptor_t weightDesc;
  cudnnFilterDescriptor_t dweightDesc;
  cudnnConvolutionDescriptor_t convDesc;
  cudnnConvolutionFwdAlgo_t fw_algo;
  cudnnConvolutionBwdDataAlgo_t bd_algo;
  cudnnConvolutionBwdFilterAlgo_t bf_algo;
#endif
#endif
};

typedef enum {
  CONSTANT,
  STEP,
  EXP,
  POLY,
  STEPS,
  SIG,
  RANDOM
} learning_rate_policy;

typedef struct network {
  int n;
  int batch;
  size_t *seen;
  int *t;
  float epoch;
  int subdivisions;
  layer *layers;
  float *output;
  learning_rate_policy policy;

  float learning_rate;
  float momentum;
  float decay;
  float gamma;
  float scale;
  float power;
  int time_steps;
  int step;
  int max_batches;
  float *scales;
  int *steps;
  int num_steps;
  int burn_in;

  int adam;
  float B1;
  float B2;
  float eps;

  int gpu_index;
  int inputs;
  int outputs;
  int truths;
  int notruth;
  int h, w, c;
  int max_crop;
  int min_crop;
  float max_ratio;
  float min_ratio;
  int center;
  float angle;
  float aspect;
  float exposure;
  float saturation;
  float hue;
  int random;
  tree *hierarchy;
  float *input;
  float *truth;
  float *delta;
  float *workspace;
  int train;
  int index;
  float *cost;
  float clip;
#ifdef GPU
  float *input_gpu;
  float *truth_gpu;
  float *delta_gpu;
  float *output_gpu;
#endif

} network;
typedef struct {
  int w;
  int h;
  int c;
  float *data;
} image;
typedef enum {
  CLASSIFICATION_DATA,
  DETECTION_DATA,
  CAPTCHA_DATA,
  REGION_DATA,
  IMAGE_DATA,
  SWAG_DATA,
  TAG_DATA,
  OLD_CLASSIFICATION_DATA,
  STUDY_DATA,
  DET_DATA,
  SUPER_DATA,
  LETTERBOX_DATA,
  REGRESSION_DATA,
  INSTANCE_DATA,
  ISEG_DATA,
} data_type;

typedef struct load_args {
  int threads;
  char **paths;
  int n;
  int m;
  char **labels;
  int h;
  int w;
  int out_w;
  int out_h;
  int nh;
  int num_boxes;
  int min, max, size;
  int classes;
  int backgroud;
  int saturation;
  int scale;
  int center;
  int coords;
  int jitter;
  float angle;
  float aspect;
  float exposure;
  float hue;
  data *d;
  image *im;
  image *resized;
  data_type type;
  tree *hierarchy;
} load_args;

typedef layer route_layer;
void malloc_error() {
  fprintf(stderr, "Malloc error\n");
  exit(-1);
}

char *fgetl(FILE *fp) {
  if (feof(fp))
    return 0;
  size_t size = 512;
  char *line = malloc(size * sizeof(char));
  if (!fgets(line, size, fp)) {
    free(line);
    return 0;
  }
  size_t curr = strlen(line);
  while ((line[curr - 1] != '\n') && !feof(fp)) {
    if (curr == size - 1) {
      size *= 2;
      line = realloc(line, size * sizeof(char));
      if (!line) {
        printf("%ld\n", size);
        malloc_error();
      }
    }
    size_t readsize = size - curr;
    if (readsize > INT_MAX)
      readsize = INT_MAX - 1;
    fgets(&line[curr], readsize, fp);
    curr = strlen(line);
  }
  if (line[curr - 1] == '\n')
    line[curr - 1] = '\0';
  return line;
}

void strip(char *s) {
  size_t i;
  size_t len = strlen(s);
  size_t offset = 0;
  for (i = 0; i < len; ++i) {
    char c = s[i];
    if (c == ' ' || c == '\t' || c == '\n')
      ++offset;
    else
      s[len - offset] = c;
  }
  s[len - offset] = '\0';
}

typedef struct {
  char *key;
  char *val;
  int used;
} kvp;

void del_arg(int argc, char **argv, int index) {
  int i;
  for (i = index; i < argc - 1; ++i) {
    argv[i] = argv[i + 1];
  }
  argv[i] = 0;
}

float find_float_arg(int argc, char **argv, char *arg, float def) {
  int i;
  for (i = 0; i < argc - 1; ++i) {
    if (!argv[i])
      continue;
    if (0 == strcmp(argv[i], arg)) {
      def = atof(argv[i + 1]);
      del_arg(argc, argv, i);
      del_arg(argc, argv, i);
      break;
    }
  }
  return def;
}

char *find_char_arg(int argc, char **argv, char *arg, char *def) {
  int i;
  for (i = 0; i < argc - 1; ++i) {
    if (!argv[i])
      continue;
    if (0 == strcmp(argv[i], arg)) {
      def = argv[i + 1];
      del_arg(argc, argv, i);
      del_arg(argc, argv, i);
      break;
    }
  }
  return def;
}

int find_int_arg(int argc, char **argv, char *arg, int def) {
  int i;
  for (i = 0; i < argc - 1; ++i) {
    if (!argv[i])
      continue;
    if (0 == strcmp(argv[i], arg)) {
      def = atoi(argv[i]);
      del_arg(argc, argv, i);
      del_arg(argc, argv, i);
      break;
    }
  }
  return def;
}

extern int gpu_index;

int find_arg(int argc, char **argv, char *arg) {
  int i;
  for (i = 0; i < argc - 1; ++i) {
    if (!argv[i])
      continue;
    if (0 == strcmp(argv[i], arg)) {
      del_arg(argc, argv, i);
      return 1;
    }
  }
  return 0;
}

void file_error(char *filename) {
  fprintf(stderr, "Malloc error\n");
  exit(-1);
}

list *make_list() {
  list *l = malloc(sizeof(list));
  l->size = 0;
  l->front = 0;
  l->back = 0;
  return l;
}
void list_insert(list *l, void *val) {
  node *new = malloc(sizeof(node));
  new->val = val;
  new->next = 0;
  if (!l->back) {
    l->front = new;
    new->prev = 0;
  } else {
    l->back->next = new;
    new->prev = l->back;
  }
  l->back = new;
  ++l->size;
}

void option_insert(list *l, char *key, char *val) {
  kvp *p = malloc(sizeof(kvp));
  p->key = key;
  p->val = val;
  p->used = 0;
  list_insert(l, p);
}
int read_option(char *s, list *options) {
  size_t i;
  size_t len = strlen(s);
  char *val = 0;
  for (i = 0; i < len; ++i) {
    if (s[i] == '=') {
      s[i] = '\0';
      val = s + i + 1;
      break;
    }
  }
  if (i == len - 1)
    return 0;
  char *key = s;
  option_insert(options, key, val);
  return 1;
}
list *read_data_cfg(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == 0)
    file_error(filename);
  char *line;
  int nu = 0;
  list *options = make_list();
  while ((line = fgetl(file)) != 0) {
    ++nu;
    strip(line);
    switch (line[0]) {
    case '\0':
    case '#':
    case ';':
      free(line);
      break;
    default:
      if (!read_option(line, options)) {
        fprintf(stderr, "Config file error line %d, could parse: %s\n", nu,
                line);
        free(line);
      }
      break;
    }
    fclose(file);
    return options;
  }
  list *l;
  return l;
}

char *option_find(list *l, char *key) {
  node *n = l->front;
  while (n) {
    kvp *p = (kvp *)n->val;
    if (strcmp(p->key, key) == 0) {
      p->used = 1;
      return p->val;
    }
    n = n->next;
  }
  return 0;
}

char *copy_string(char *s) {
  char *copy = malloc(strlen(s) + 1);
  strncpy(copy, s, strlen(s) + 1);
  return copy;
}

char *basecfg(char *cfgfile) {
  char *c = cfgfile;
  char *next;
  while ((next = strchr(c, '/'))) {
    c = next + 1;
  }
  c = copy_string(c);
  next = strchr(c, '.');
  if (next)
    *next = 0;
  return c;
}

list *read_cfg(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == 0)
    file_error(filename);
  char *line;
  int nu = 0;
  list *options = make_list();
  section *current = 0;
  while ((line = fgetl(file)) != 0) {
    ++nu;
    strip(line);
    switch (line[0]) {
    case '[':
      current = malloc(sizeof(section));
      list_insert(options, current);
      current->options = make_list();
      current->type = line;
      break;
    case '\0':
    case '#':
    case ';':
      free(line);
      break;
    default:
      if (!read_option(line, current->options)) {
        fprintf(stderr, "Config file error line %d, could parser: %s\n", nu,
                line);
        free(line);
      }
      break;
    }
  }
  fclose(file);
  return options;
}

void error(const char *s) {
  perror(s);
  assert(0);
  exit(-1);
}
network *make_network(int n) {
  network *net = calloc(1, sizeof(network));
  net->n = n;
  net->layers = calloc(net->n, sizeof(layer));
  net->seen = calloc(1, sizeof(size_t));
  net->t = calloc(1, sizeof(int));
  net->cost = calloc(1, sizeof(float));
  return net;
}
typedef struct {
  int batch;
  int inputs;
  int h;
  int w;
  int c;
  int index;
  int time_steps;
  network *net;
} size_params;

int is_network(section *s) {
  return (strcmp(s->type, "[net]") == 0 || strcmp(s->type, "[network]") == 0);
}
char *option_find_str(list *l, char *key, char *def) {
  char *v = option_find(l, key);
  if (v)
    return v;
  if (def)
    fprintf(stderr, "%s: Using default '%s'\n", key, def);
  return def;
}

int option_find_int(list *l, char *key, int def) {
  char *v = option_find(l, key);
  if (v)
    return atoi(v);
  fprintf(stderr, "%s: Using default '%d'\n", key, def);
  return def;
}

int option_find_int_quiet(list *l, char *key, int def) {
  char *v = option_find(l, key);
  if (v)
    return atoi(v);
  return def;
}

float option_find_float_quiet(list *l, char *key, float def) {
  char *v = option_find(l, key);
  if (v)
    return atof(v);
  return def;
}

float option_find_float(list *l, char *key, float def) {
  char *v = option_find(l, key);
  if (v)
    return atof(v);
  fprintf(stderr, "%s: Using default '%lf'\n", key, def);
  return def;
}
learning_rate_policy get_policy(char *s) {
  if (strcmp(s, "random") == 0)
    return RANDOM;
  if (strcmp(s, "poly") == 0)
    return POLY;
  if (strcmp(s, "constant") == 0)
    return CONSTANT;
  if (strcmp(s, "step") == 0)
    return STEP;
  if (strcmp(s, "exp") == 0)
    return EXP;
  if (strcmp(s, "sigmoid") == 0)
    return SIG;
  if (strcmp(s, "steps") == 0)
    return STEPS;
  fprintf(stderr, "Couldn't find policy %s, going with constant\n", s);
  return CONSTANT;
}

void parse_net_options(list *options, network *net) {
  net->batch = option_find_int(options, "batch", 1);
  net->learning_rate = option_find_float(options, "learning_rate", .001);
  net->momentum = option_find_float(options, "momentum", .9);
  net->decay = option_find_float(options, "decay", .0001);
  int subdivs = option_find_int(options, "subdivisons", 1);
  net->time_steps = option_find_int_quiet(options, "time_steps", 1);
  net->notruth = option_find_int_quiet(options, "notruth", 0);
  net->batch /= subdivs;
  net->batch *= net->time_steps;
  net->subdivisions = subdivs;
  net->random = option_find_int(options, "random", 0);
  net->adam = option_find_int(options, "adam", 0);
  if (net->adam) {
    net->B1 = option_find_float(options, "B1", .9);
    net->B2 = option_find_float(options, "B2", .999);
    net->eps = option_find_float(options, "eps", 0.0000001);
  }
  net->h = option_find_int(options, "height", 0);
  net->w = option_find_int(options, "width", 0);
  net->c = option_find_int(options, "channels", 0);
  net->inputs = option_find_int(options, "inputs", net->h * net->w * net->c);
  net->max_crop = option_find_int(options, "max_crop", net->w * 2);
  net->min_crop = option_find_int(options, "min_crop", net->w);
  net->max_ratio =
      option_find_float(options, "max_ratio", (float)net->max_crop / net->w);
  net->min_ratio =
      option_find_float(options, "min_ratio", (float)net->min_crop / net->w);
  net->center = option_find_int(options, "center", 0);
  net->clip = option_find_float(options, "clip", 0);
  net->angle = option_find_float(options, "angel", 0);
  net->aspect = option_find_float(options, "ascpet", 1);
  net->saturation = option_find_float(options, "saturation", 1);
  net->exposure = option_find_float(options, "exposure", 1);
  net->hue = option_find_float(options, "hue", 0);
  if (!net->inputs && !(net->h && net->w && net->c))
    error("No  input parameters supplied");
  char *policy_s = option_find_str(options, "policy", "constant");
  net->policy = get_policy(policy_s);
  net->burn_in = option_find_int(options, "burn_in", 0);
  net->power = option_find_float(options, "power", 4);
  if (net->policy == STEP) {
    net->step = option_find_int(options, "power", 4);
    net->scale = option_find_int(options, "scale", 1);
  } else if (net->policy == STEPS) {
    char *l = option_find(options, "steps");
    char *p = option_find(options, "scales");
    if (!l || !p)
      error("");
    int len = strlen(l);
    int n = 1;
    int i;
    for (i = 0; i < len; ++i) {
      if (l[i] == ',')
        ++n;
    }
    int *steps = calloc(n, sizeof(int));
    float *scales = calloc(n, sizeof(float));
    for (i = 0; i < n; ++i) {
      int step = atoi(l);
      float scale = atof(p);
      l = strchr(l, ',') + 1;
      p = strchr(p, ',') + 1;
      steps[i] = step;
      scales[i] = scale;
    }
    net->scales = scales;
    net->steps = steps;
    net->num_steps = n;
  } else if (net->policy == EXP) {
    net->gamma = option_find_float(options, "gamma", 1);
  } else if (net->policy == SIG) {
    net->gamma = option_find_float(options, "gamma", 1);
    net->step = option_find_int(options, "step", 1);
  } else if (net->policy == POLY || net->policy == RANDOM) {
  }
  net->max_batches = option_find_int(options, "max_batches", 0);
}

void free_section(section *s) {
  free(s->type);
  node *n = s->options->front;
  while (n) {
    kvp *pair = (kvp *)n->val;
    free(pair->key);
    free(pair);
    node *next = n->next;
    free(n);
    n = next;
  }
  free(s->options);
  free(s);
}
typedef layer local_layer;
local_layer parse_local(list *optons, size_params params) {
  int n = option_find_int(options, "filterd", 1); 
  int size = option_find_int(options, "size", 1);
}
LAYER_TYPE string_to_layer_type(char *type) {

  if (strcmp(type, "[shortcut]") == 0)
    return SHORTCUT;
  if (strcmp(type, "[crop]") == 0)
    return CROP;
  if (strcmp(type, "[cost]") == 0)
    return COST;
  if (strcmp(type, "[detection]") == 0)
    return DETECTION;
  if (strcmp(type, "[region]") == 0)
    return REGION;
  if (strcmp(type, "[yolo]") == 0)
    return YOLO;
  if (strcmp(type, "[iseg]") == 0)
    return ISEG;
  if (strcmp(type, "[local]") == 0)
    /* l = parse_local(options, params); */
    return LOCAL;
  if (strcmp(type, "[conv]") == 0 || strcmp(type, "[convolutional]") == 0)
    return CONVOLUTIONAL;
  if (strcmp(type, "[deconv]") == 0 || strcmp(type, "[deconvolutional]") == 0)
    return DECONVOLUTIONAL;
  if (strcmp(type, "[activation]") == 0)
    return ACTIVE;
  if (strcmp(type, "[logistic]") == 0)
    return LOGXENT;
  if (strcmp(type, "[l2norm]") == 0)
    return L2NORM;
  if (strcmp(type, "[net]") == 0 || strcmp(type, "[network]") == 0)
    return NETWORK;
  if (strcmp(type, "[crnn]") == 0)
    return CRNN;
  if (strcmp(type, "[gru]") == 0)
    return GRU;
  if (strcmp(type, "[lstm]") == 0)
    return LSTM;
  if (strcmp(type, "[rnn]") == 0)
    return RNN;
  if (strcmp(type, "[conn]") == 0 || strcmp(type, "[connected]") == 0)
    return CONNECTED;
  if (strcmp(type, "[max]") == 0 || strcmp(type, "[maxpool]") == 0)
    return MAXPOOL;
  if (strcmp(type, "[reorg]") == 0)
    return REORG;
  if (strcmp(type, "[avg]") == 0 || strcmp(type, "[avgpool]") == 0)
    return AVGPOOL;
  if (strcmp(type, "[dropout]") == 0)
    return DROPOUT;
  if (strcmp(type, "[lrn]") == 0 || strcmp(type, "[normalization]") == 0)
    return NORMALIZATION;
  if (strcmp(type, "[batchnorm]") == 0)
    return BATCHNORM;
  if (strcmp(type, "[soft]") == 0 || strcmp(type, "[softmax]") == 0)
    return SOFTMAX;
  if (strcmp(type, "[route]") == 0)
    return ROUTE;
  if (strcmp(type, "[upsample]") == 0)
    return UPSAMPLE;
  return BLANK;
}

typedef layer convolutional_layer;
ACTIVATION get_activation(char *s) {
  if (strcmp(s, "logistic") == 0)
    return LOGISTIC;
  if (strcmp(s, "loggy") == 0)
    return LOGGY;
  if (strcmp(s, "relu") == 0)
    return RELU;
  if (strcmp(s, "elu") == 0)
    return ELU;
  if (strcmp(s, "selu") == 0)
    return SELU;
  if (strcmp(s, "relie") == 0)
    return RELIE;
  if (strcmp(s, "plse") == 0)
    return PLSE;
  if (strcmp(s, "hardtan") == 0)
    return HARDTAN;
  if (strcmp(s, "lhtan") == 0)
    return LHTAN;
  if (strcmp(s, "linear") == 0)
    return LINEAR;
  if (strcmp(s, "ramp") == 0)
    return RAMP;
  if (strcmp(s, "leaky") == 0)
    return LEAKY;
  if (strcmp(s, "tanh") == 0)
    return TANH;
  if (strcmp(s, "stair") == 0)
    return STAIR;
  fprintf(stderr, "Couldn't find activation function %s, going with ReLU\n", s);
  return RELU;
}

#define TWO_PI 6.2831853071795864769252866f
float rand_normal() {
  static int haveSpare = 0;
  static double rand1, rand2;

  if (haveSpare) {
    haveSpare = 0;
    return sqrt(rand1) * sin(rand2);
  }

  haveSpare = 1;

  rand1 = rand() / ((double)RAND_MAX);
  if (rand1 < 1e-100)
    rand1 = 1e-100;
  rand1 = -2 * log(rand1);
  rand2 = (rand() / ((double)RAND_MAX)) * TWO_PI;

  return sqrt(rand1) * cos(rand2);
}
int convolutional_out_height(convolutional_layer l) {
  return (l.h + 2 * l.pad - l.size) / l.stride + 1;
}

int convolutional_out_width(convolutional_layer l) {
  return (l.w + 2 * l.pad - l.size) / l.stride + 1;
}

static size_t get_workspace_size(layer l) {
#ifdef CUDNN
  if (gpu_index >= 0) {
    size_t most = 0;
    size_t s = 0;
    cudnnGetConvolutionForwardWorkspaceSize(cudnn_handle(), l.srcTensorDesc,
                                            l.weightDesc, l.convDesc,
                                            l.dstTensorDesc, l.fw_algo, &s);
    if (s > most)
      most = s;
    cudnnGetConvolutionBackwardFilterWorkspaceSize(
        cudnn_handle(), l.srcTensorDesc, l.ddstTensorDesc, l.convDesc,
        l.dweightDesc, l.bf_algo, &s);
    if (s > most)
      most = s;
    cudnnGetConvolutionBackwardDataWorkspaceSize(
        cudnn_handle(), l.weightDesc, l.ddstTensorDesc, l.convDesc,
        l.dsrcTensorDesc, l.bd_algo, &s);
    if (s > most)
      most = s;
    return most;
  }
#endif
  return (size_t)l.out_h * l.out_w * l.size * l.size * l.c / l.groups *
         sizeof(float);
}
void fill_cpu(int N, float ALPHA, float *X, int INCX) {
  int i;
  for (i = 0; i < N; ++i)
    X[i * INCX] = ALPHA;
}
void binarize_weights(float *weights, int n, int size, float *binary) {
  int i, f;
  for (f = 0; f < n; ++f) {
    float mean = 0;
    for (i = 0; i < size; ++i) {
      mean += fabs(weights[f * size + i]);
    }
    mean = mean / size;
    for (i = 0; i < size; ++i) {
      binary[f * size + i] = (weights[f * size + i] > 0) ? mean : -mean;
    }
  }
}
void swap_binary(convolutional_layer *l) {
  float *swap = l->weights;
  l->weights = l->binary_weights;
  l->binary_weights = swap;

#ifdef GPU
  swap = l->weights_gpu;
  l->weights_gpu = l->binary_weights_gpu;
  l->binary_weights_gpu = swap;
#endif
}
void binarize_cpu(float *input, int n, float *binary) {
  int i;
  for (i = 0; i < n; ++i) {
    binary[i] = (input[i] > 0) ? 1 : -1;
  }
}
float im2col_get_pixel(float *im, int height, int width, int channels, int row,
                       int col, int channel, int pad) {
  row -= pad;
  col -= pad;
  if (row < 0 || col < 0 || row >= height || col >= width) {
    return 0;
  }
  return im[col + width * (row + height * channel)];
}

void im2col_cpu(float *data_im, int channels, int height, int width, int ksize,
                int stride, int pad, float *data_col) {
  int c, w, h;
  int height_col = (height + 2 * pad - ksize) / stride + 1;
  int width_col = (height + 2 * pad - ksize) / stride + 1;
  int channels_col = channels * ksize * ksize;

  for (c = 0; c < channels_col; ++c) {
    int w_offset = c % ksize;
    int h_offset = (c / ksize) % ksize;
    int c_im = c / ksize / ksize;
    for (h = 0; h < height_col; ++h) {
      for (w = 0; w < width_col; ++w) {
        int im_row = h_offset + h * stride;
        int im_col = w_offset + w * stride;
        int col_index = (c * height_col + h) * width_col + w;
        data_col[col_index] = im2col_get_pixel(data_im, height, width, channels,
                                               im_row, im_col, c_im, pad);
      }
    }
  }
}

void gemm_nn(int M, int N, int K, float ALPHA, float *A, int lda, float *B,
             int ldb, float *C, int ldc) {
  int i, j, k;
#pragma omp parallel for
  for (i = 0; i < M; ++i) {
    for (k = 0; k < K; ++k) {
      register float A_PART = ALPHA * A[i * lda + k];
      for (j = 0; j < N; ++j) {
        C[i * ldc + j] = A_PART * B[k * ldb + j];
      }
    }
  }
}

void gemm_nt(int M, int N, int K, float ALPHA, float *A, int lda, float *B,
             int ldb, float *C, int ldc) {
  int i, j, k;
  for (i = 0; i < M; ++i) {
    for (j = 0; j < N; ++j) {
      register float sum = 0;
      for (k = 0; k < K; ++k) {
        sum += ALPHA * A[i * lda + k] * B[j * ldb + k];
      }
      C[i * ldc + j] += sum;
    }
  }
}

/* void gem_tn(int M, int N, int K, float ALPHA, float *A, int lda, float *B, */
/*             int ldb, float *C, int ldc) { */
/*   int i, j, k; */
/* #pragma omp parallel for */
/*   for (i = 0; j < M; ++i) { */
/*     for(k =0; k  < K; ++k) { */
/*       register float A_PART=   */
/*     } */
/*   } */
/* } */

void gemm_cpu(int TA, int TB, int M, int N, int K, float ALPHA, float *A,
              int lda, float *B, int ldb, float BETA, float *C, int ldc) {
  int i, j;
  for (i = 0; i < M; ++i) {
    for (j = 0; j < N; ++j) {
      C[i * ldc + j] *= BETA;
    }
  }
  if (!TA && !TB) {
    gemm_nn(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
  } else if (TA && !TB) {
    /* gemm_tn(M, N, K, ALPHA, A, lda, B, ldb, C, ldc); */
  } else if (!TA && TB) {
    gemm_nt(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
  } else {
    /* gemm_tt(M, N, K, ALPHA, A, lda, B, ldb, C, ldc); */
  }
}

void gemm(int TA, int TB, int M, int N, int K, float ALPHA, float *A, int lda,
          float *B, int ldb, float BETA, float *C, int ldc) {
  gemm_cpu(TA, TB, M, N, K, ALPHA, A, lda, B, ldb, BETA, C, ldc);
}

void copy_cpu(int N, float *X, int INCX, float *Y, int INCY) {
  for (int i = 0; i < N; ++i) {
    Y[i * INCY] = X[i * INCX];
  }
}

void mean_cpu(float *x, int batch, int filters, int spatial, float *mean) {
  float scale = 1.0 / (batch * spatial);
  int i, j, k;
  for (i = 0; i < filters; ++i) {
    mean[i] = 0;
    for (j = 0; j < batch; ++j) {
      for (k = 0; k < spatial; ++k) {
        int index = j * filters * spatial + k;
        mean[i] += x[index];
      }
    }
  }
  mean[i] *= scale;
}

void variance_cpu(float *x, float *mean, int batch, int filters, int spatial,
                  float *variance) {
  float scale = 1. / (batch * spatial - 1);
  int i, j, k;
  for (i = 0; i < filters; ++i) {
    variance[i] = 0;
    for (j = 0; j < batch; ++j) {
      for (k = 0; k < spatial; ++k) {
        int index = j * filters * spatial + j * spatial + k;
        variance[i] += pow(x[index] - mean[i], 2);
      }
    }
    variance[i] *= scale;
  }
}
void scal_cpu(int N, float ALPHA, float *X, int INCX) {
  int i;
  for (i = 0; i < N; ++i) {
    X[i * INCX] *= ALPHA;
  }
}
// y = ax+y
void axpy_cpu(int N, float ALPHA, float *X, int INCX, float *Y, int INCY) {
  int i;
  for (i = 0; i < N; ++i) {
    Y[i * INCY] += ALPHA * X[i * INCX];
  }
}
void normalize_cpu(float *x, float *mean, float *variance, int batch,
                   int filters, int spatial) {
  int b, f, i;
  for (b = 0; b < batch; ++b) {
    for (f = 0; f < filters; ++f) {
      for (i = 0; i < spatial; ++i) {
        int index = b * filters * spatial + f * spatial + i;
        x[index] = (x[index] - mean[f]) / (sqrt(variance[f]) + 0.000001f);
      }
    }
  }
}

void add_bias(float *output, float *biases, int batch, int n, int size) {
  int i, j, b;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < size; ++j) {
      output[(b * n + i) * size + j] += biases[i];
    }
  }
}

void scale_bias(float *output, float *scales, int batch, int n, int size) {
  int i, j, b;
  for (b = 0; b < batch; ++b) {
    for (i = 0; i < n; ++j) {
      for (j = 0; j < size; ++j) {
        output[(b * n + i) * size + j] *= scales[j];
      }
    }
  }
}

void forward_batchnorm_layer(layer l, network net) {
  if (l.type == BATCHNORM) {
    copy_cpu(l.outputs * l.batch, net.input, 1, l.output, 1);
  }
  copy_cpu(l.outputs * l.batch, l.output, 1, l.x, 1);
  if (net.train) {
    mean_cpu(l.output, l.batch, l.out_c, l.out_w * l.out_h, l.mean);
    variance_cpu(l.output, l.mean, l.batch, l.out_c, l.out_w * l.out_h,
                 l.variance);
    scal_cpu(l.out_c, .99, l.rolling_mean, 1);

    scal_cpu(l.out_c, .99, l.rolling_variance, 1);
    axpy_cpu(l.out_c, .01, l.variance, 1, l.rolling_variance, 1);
  } else {
    normalize_cpu(l.output, l.mean, l.variance, l.batch, l.out_c,
                  l.out_w * l.out_h);
    copy_cpu(l.outputs * l.batch, l.output, 1, l.x_norm, 1);
  }
  scale_bias(l.output, l.scales, l.batch, l.out_c, l.out_h * l.out_w);
  add_bias(l.output, l.biases, l.batch, l.out_c, l.out_w * l.out_h);
}

static inline float linear_activate(float x) { return x; }
static inline float logistic_activate(float x) { return 1. / (1. + exp(-x)); }
static inline float loggy_activate(float x) { return 2. / (1. + exp(-x)) - 1; }
static inline float relu_activate(float x) { return x * (x > 0); }
static inline float elu_activate(float x) {
  return (x >= 0) * x + (x < 0) * (exp(-x) - 1);
}

static inline float selu_activate(float x) {
  return (x >= 0) * 1.0507 * x + (x < 0) * 1.0507 * 1.6732 * (exp(x) - 1);
}
static inline float relie_activate(float x) { return (x > 0) ? x : 0.1 * x; }

static inline float ramp_activate(float x) { return (x > 0) ? x : 0.1 * x; }
static inline float leaky_activate(float x) { return (x > 0) ? x : 0.1 * x; }
static inline float tanh_activate(float x) {
  return (exp(2 * x) - 1) / (exp(2 * x) + 1);
}
static inline float plse_activate(float x) {
  if (x < -4)
    return .01 * (x + 4);
  if (x > 4)
    return .01 * (x - 4) + 1;
  return .125 * x + .5;
}

float activate(float x, ACTIVATION a) {
  /* switch(a) { */
  /* case LINEAR: */
  /* return linear_activate(x); */
  /* case LOGISTIC:  */
  /* return logistic_activate(x); */
  /* case LOGGY: */
  /* return loggy_activate(x); */
  /* case RELU: */
  /* return relu_activate(x); */
  /* case ELU: */
  /* return elu_activate(x);  */
  /* case SELU: */
  /* return selu_activate(); */
  /* case ramp_activate(float x) { */
  /* return (x>0) ? x : 0.1*x;  */
  /* } */
  /* case leaky_activate(float ) */
  /* } */
  return 0;
}
void activate_array(float *x, const int n, const ACTIVATION a) {
  int i;
  for (i = 0; i < n; ++i) {
    x[i] = activate(x[i], a);
  }
}
void forward_convolutional_layer(convolutional_layer l, network net) {
  int i, j;

  fill_cpu(l.outputs * l.batch, 0, l.output, 1);

  if (l.xnor) {
    binarize_weights(l.weights, l.n, l.c / l.groups * l.size * l.size,
                     l.binary_weights);
    swap_binary(&l);
    binarize_cpu(net.input, l.c * l.h * l.w * l.batch, l.binary_input);
    net.input = l.binary_input;
  }

  int m = l.n / l.groups;
  int k = l.size * l.size * l.c / l.groups;
  int n = l.out_w * l.out_h;
  for (i = 0; i < l.batch; ++i) {
    for (j = 0; j < l.groups; ++j) {
      float *a = l.weights + j * l.nweights / l.groups;
      float *b = net.workspace;
      float *c = l.output + (i * l.groups + j) * n * m;
      float *im = net.input + (i * l.groups + j) * l.c / l.groups * l.h * l.w;

      if (l.size == 1) {
        b = im;
      } else {
        im2col_cpu(im, l.c / l.groups, l.h, l.w, l.size, l.stride, l.pad, b);
      }
      gemm(-1, 0, m, n, k, 1, a, k, b, n, 1, c, n);
    }
  }

  if (l.batch_normalize) {
    forward_batchnorm_layer(l, net);
  } else {
    add_bias(l.output, l.biases, l.batch, l.n, l.out_h * l.out_w);
  }

  activate_array(l.output, l.outputs * l.batch, l.activation);
  if (l.binary || l.xnor)
    swap_binary(&l);
}
static inline float lhtan_gradient(float x) {
  if (x > 0 && x < 1)
    return 1;
  return .001;
}

static inline float hardtan_gradient(float x) {
  if (x > -1 && x < 1)
    return 1;
  return 0;
}
static inline float linear_gradient(float x) { return 1; }
static inline float logistic_gradient(float x) { return (1 - x) * x; }
static inline float loggy_gradient(float x) {
  float y = (x + 1.) / 2.;
  return 2 * (1 - y) * y;
}
static inline float stair_gradient(float x) {
  if (floor(x) == x)
    return 0;
  return 1;
}
static inline float relu_gradient(float x) { return (x > 0); }
static inline float elu_gradient(float x) {
  return (x >= 0) + (x < 0) * (x + 1);
}
static inline float selu_gradient(float x) {
  return (x >= 0) * 1.0507 + (x < 0) * (x + 1.0507 * 1.6732);
}
static inline float relie_gradient(float x) { return (x > 0) ? 1 : .01; }
static inline float ramp_gradient(float x) { return (x > 0) + .1; }
static inline float leaky_gradient(float x) { return (x > 0) ? 1 : .1; }
static inline float tanh_gradient(float x) { return 1 - x * x; }
static inline float plse_gradient(float x) {
  return (x < 0 || x > 1) ? .01 : .125;
}

float gradient(float x, ACTIVATION a) {
  switch (a) {
  case LINEAR:
    return linear_gradient(x);
  case LOGISTIC:
    return logistic_gradient(x);
  case LOGGY:
    return loggy_gradient(x);
  case RELU:
    return relu_gradient(x);
  case ELU:
    return elu_gradient(x);
  case SELU:
    return selu_gradient(x);
  case RELIE:
    return relie_gradient(x);
  case RAMP:
    return ramp_gradient(x);
  case LEAKY:
    return leaky_gradient(x);
  case TANH:
    return tanh_gradient(x);
  case PLSE:
    return tanh_gradient(x);
  case STAIR:
    return stair_gradient(x);
  case HARDTAN:
    return hardtan_gradient(x);
  case LHTAN:
    return lhtan_gradient(x);
  }
  return 0;
}
void gradient_array(const float *x, const int n, const ACTIVATION a,
                    float *delta) {
  int i;
  for (i = 0; i < n; ++i) {
    delta[i] *= gradient(x[i], a);
  }
}

float sum_array(float *a, int n) {
  int i;
  float sum = 0;
  for (i = 0; i < n; ++i) {
    sum += a[i];
  }
  return sum;
}
void backward_bias(float *bias_updates, float *delta, int batch, int n,
                   int size) {
  int i, b;
  for (b = 0; b < batch; ++b) {
    for (i = 0; i < n; ++i) {
      bias_updates[i] += sum_array(delta + size * (i + b * n), size);
    }
  }
}
void backward_scale_cpu(float *x_norm, float *delta, int batch, int n, int size,
                        float *scale_updates) {
  int i, b, f;
  for (f = 0; f < n; ++f) {
    float sum = 0;
    for (b = 0; b < batch; ++b) {
      for (i = 0; i < size; ++i) {
        int index = i + size * (f + n * b);
        sum += delta[index] * x_norm[index];
      }
    }
    scale_updates[f] += sum;
  }
}
void mean_delta_cpu(float *delta, float *variance, int batch, int filters,
                    int spatial, float *mean_delta) {
  int i, j, k;
  for (i = 0; i < filters; ++i) {
    mean_delta[i] = 0;
    for (j = 0; j < batch; ++j) {
      for (k = 0; k < spatial; ++k) {
        int index = j * filters * spatial + i * spatial + k;
        mean_delta[i] += delta[index];
      }
    }
    mean_delta[i] *= (-1. / sqrt(variance[i] + 0.00001f));
  }
}
void variance_delta_cpu(float *x, float *delta, float *mean, float *variance,
                        int batch, int filters, int spatial,
                        float *variance_delta) {
  int i, j, k;
  for (i = 0; i < filters; ++i) {
    variance_delta[i] = 0;
    for (j = 0; j < batch; ++j) {
      for (k = 0; k < spatial; ++k) {
        int index = j * filters * spatial + i * spatial + k;
        variance_delta[i] += delta[index] * (x[index] - mean[i]);
      }
    }
  }
}
void normalize_delta_cpu(float *x, float *mean, float *variance,
                         float *mean_delta, float *variance_delta, int batch,
                         int filters, int spatial, float *delta) {
  int f, j, k;
  for (j = 0; j < batch; ++j) {
    for (f = 0; f < filters; ++f) {
      for (k = 0; k < spatial; ++k) {
        int index = j * filters * spatial + f * spatial + k;
        delta[index] =
            delta[index] * 1. / (sqrt(variance[f] + .00001f)) +
            variance_delta[f] * 2. * (x[index] - mean[f]) / (spatial * batch) +
            mean_delta[f] / (spatial * batch);
      }
    }
  }
}

void backward_batchnorm_layer(layer l, network net) {
  if (!net.train) {
    l.mean = l.rolling_mean;
    l.variance = l.rolling_variance;
  }
  backward_bias(l.bias_updates, l.delta, l.batch, l.out_c, l.out_w * l.out_h);
  backward_scale_cpu(l.x_norm, l.delta, l.batch, l.out_c, l.out_w * l.out_h,
                     l.scale_updates);
  scale_bias(l.output, l.scales, l.batch, l.out_c, l.out_w * l.out_h);
  mean_delta_cpu(l.delta, l.variance, l.batch, l.out_c, l.out_w * l.out_h,
                 l.mean_delta);
  variance_delta_cpu(l.x, l.delta, l.mean, l.variance, l.batch, l.out_c,
                     l.out_w * l.out_h, l.mean_delta);
  normalize_delta_cpu(l.x, l.mean, l.variance, l.mean_delta, l.variance_delta,
                      l.batch, l.out_c, l.out_w * l.out_h, l.variance_delta);
  if (l.type == BATCHNORM) {
    copy_cpu(l.outputs * l.batch, l.delta, 1, net.delta, 1);
  }
}

void col2im_add_pixel(float *im, int height, int width, int channels, int row,
                      int col, int channel, int pad, float val) {
  row -= pad;
  col -= pad;

  if (row < 0 || col < 0 || row >= height || col >= width)
    return;
  im[col + width * (row + height * channel)] += val;
}
// This one might be too, can't remember.
void col2im_cpu(float *data_col, int channels, int height, int width, int ksize,
                int stride, int pad, float *data_im) {
  int c, h, w;
  int height_col = (height + 2 * pad - ksize) / stride + 1;
  int width_col = (width + 2 * pad - ksize) / stride + 1;

  int channels_col = channels * ksize * ksize;
  for (c = 0; c < channels_col; ++c) {
    int w_offset = c % ksize;
    int h_offset = (c / ksize) % ksize;
    int c_im = c / ksize / ksize;
    for (h = 0; h < height_col; ++h) {
      for (w = 0; w < width_col; ++w) {
        int im_row = h_offset + h * stride;
        int im_col = w_offset + w * stride;
        int col_index = (c * height_col + h) * width_col + w;
        double val = data_col[col_index];
        col2im_add_pixel(data_im, height, width, channels, im_row, im_col, c_im,
                         pad, val);
      }
    }
  }
}

void backward_convolutional_layer(convolutional_layer l, network net) {
  int i, j;
  int m = l.n / l.groups;
  int n = l.size * l.size * l.c / l.groups;
  int k = l.out_w * l.out_h;
  gradient_array(l.output, l.outputs * l.batch, l.activation, l.delta);

  if (l.batch_normalize) {
    backward_batchnorm_layer(l, net);
  } else {
    backward_bias(l.bias_updates, l.delta, l.batch, l.n, k);
  }
  for (i = 0; i < l.batch; ++i) {
    for (j = 0; j < l.groups; ++j) {
      float *a = l.delta + (i * l.groups + j) * m * k;
      float *b = net.workspace;
      float *c =
          l.weight_updates + (i * l.groups + j) * l.c / l.groups * l.h * l.w;

      float *im = net.input + (i * l.groups + j) * l.c / l.groups * l.h * l.w;
      float *imd = net.delta + (i * l.groups + j) * l.c / l.groups * l.h * l.w;
      if (l.size == 1) {
        b = im;
      } else {
        im2col_cpu(im, l.c / l.groups, l.h, l.w, l.size, l.stride, l.pad, b);
      }
      gemm(0, 1, m, n, k, 1, a, k, b, k, 1, c, n);
      if (net.delta) {
        a = l.weights + j * l.nweights / l.groups;
        b = l.delta + (i * l.groups + j) * m * k;
        c = net.workspace;
        if (l.size == 1) {
          c = imd;
        }
      }
      gemm(1, 0, n, k, m, 1, a, n, b, k, 0, c, k);
      if (l.size != 1) {
        col2im_cpu(net.workspace, l.c / l.groups, l.h, l.w, l.size, l.stride,
                   l.pad, imd);
      }
    }
  }
}
void update_convolutional_layer(convolutional_layer l, update_args a) {
  float learning_rate = a.learning_rate * l.learning_rate_scale;
  float momentum = a.momentum;
  float decay = a.decay;
  int batch = a.batch;
  axpy_cpu(l.n, learning_rate / batch, l.bias_updates, 1, l.biases, 1);
  scal_cpu(l.n, momentum, l.bias_updates, 1);
  if (l.scales) {
    axpy_cpu(l.n, learning_rate / batch, l.scale_updates, 1, l.scales, 1);
    scal_cpu(l.n, momentum, l.bias_updates, 1);
  }
  axpy_cpu(l.nweights, -decay * batch, l.weights, 1, l.weight_updates, 1);
  axpy_cpu(l.nweights, learning_rate, l.weight_updates, 1, l.weights, 1);
  scal_cpu(l.n, momentum, l.weight_updates, 1);
}

convolutional_layer make_convolutional_layer(int batch, int h, int w, int c,
                                             int n, int groups, int size,
                                             int stride, int padding,
                                             ACTIVATION activation,
                                             int batch_normalize, int binary,
                                             int xnor, int adam) {
  int i;
  convolutional_layer l = {0};
  l.type = CONVOLUTIONAL;

  l.groups = groups;
  l.h = h;
  l.w = w;
  l.c = c;
  l.n = n;
  l.binary = binary;
  l.xnor = xnor;
  l.batch = batch;
  l.stride = stride;
  l.size = size;
  l.pad = padding;
  l.batch_normalize = batch_normalize;

  l.weights = calloc(c / groups * n * size * size, sizeof(float));
  l.weight_updates = calloc(c / groups * n * size * size, sizeof(float));

  l.biases = calloc(n, sizeof(float));
  l.bias_updates = calloc(n, sizeof(float));

  l.nweights = c / groups * n * size * size;
  l.nbiases = n;

  // float scale = 1./sqrt(size*size*c);
  float scale = sqrt(2. / (size * size * c / l.groups));
  // printf("convscale %f\n", scale);
  // scale = .02;
  // for(i = 0; i < c*n*size*size; ++i) l.weights[i] = scale*rand_uniform(-1,
  // 1);
  for (i = 0; i < l.nweights; ++i)
    l.weights[i] = scale * rand_normal();
  int out_w = convolutional_out_width(l);
  int out_h = convolutional_out_height(l);
  l.out_h = out_h;
  l.out_w = out_w;
  l.out_c = n;
  l.outputs = l.out_h * l.out_w * l.out_c;
  l.inputs = l.w * l.h * l.c;

  l.output = calloc(l.batch * l.outputs, sizeof(float));
  l.delta = calloc(l.batch * l.outputs, sizeof(float));

  l.forward = forward_convolutional_layer;
  l.backward = backward_convolutional_layer;
  l.update = update_convolutional_layer;
  if (binary) {
    l.binary_weights = calloc(l.nweights, sizeof(float));
    l.cweights = calloc(l.nweights, sizeof(char));
    l.scales = calloc(n, sizeof(float));
  }
  if (xnor) {
    l.binary_weights = calloc(l.nweights, sizeof(float));
    l.binary_input = calloc(l.inputs * l.batch, sizeof(float));
  }

  if (batch_normalize) {
    l.scales = calloc(n, sizeof(float));
    l.scale_updates = calloc(n, sizeof(float));
    for (i = 0; i < n; ++i) {
      l.scales[i] = 1;
    }

    l.mean = calloc(n, sizeof(float));
    l.variance = calloc(n, sizeof(float));

    l.mean_delta = calloc(n, sizeof(float));
    l.variance_delta = calloc(n, sizeof(float));

    l.rolling_mean = calloc(n, sizeof(float));
    l.rolling_variance = calloc(n, sizeof(float));
    l.x = calloc(l.batch * l.outputs, sizeof(float));
    l.x_norm = calloc(l.batch * l.outputs, sizeof(float));
  }
  if (adam) {
    l.m = calloc(l.nweights, sizeof(float));
    l.v = calloc(l.nweights, sizeof(float));
    l.bias_m = calloc(n, sizeof(float));
    l.scale_m = calloc(n, sizeof(float));
    l.bias_v = calloc(n, sizeof(float));
    l.scale_v = calloc(n, sizeof(float));
  }

#ifdef GPU
  l.forward_gpu = forward_convolutional_layer_gpu;
  l.backward_gpu = backward_convolutional_layer_gpu;
  l.update_gpu = update_convolutional_layer_gpu;

  if (gpu_index >= 0) {
    if (adam) {
      l.m_gpu = cuda_make_array(l.m, l.nweights);
      l.v_gpu = cuda_make_array(l.v, l.nweights);
      l.bias_m_gpu = cuda_make_array(l.bias_m, n);
      l.bias_v_gpu = cuda_make_array(l.bias_v, n);
      l.scale_m_gpu = cuda_make_array(l.scale_m, n);
      l.scale_v_gpu = cuda_make_array(l.scale_v, n);
    }

    l.weights_gpu = cuda_make_array(l.weights, l.nweights);
    l.weight_updates_gpu = cuda_make_array(l.weight_updates, l.nweights);

    l.biases_gpu = cuda_make_array(l.biases, n);
    l.bias_updates_gpu = cuda_make_array(l.bias_updates, n);

    l.delta_gpu = cuda_make_array(l.delta, l.batch * out_h * out_w * n);
    l.output_gpu = cuda_make_array(l.output, l.batch * out_h * out_w * n);

    if (binary) {
      l.binary_weights_gpu = cuda_make_array(l.weights, l.nweights);
    }
    if (xnor) {
      l.binary_weights_gpu = cuda_make_array(l.weights, l.nweights);
      l.binary_input_gpu = cuda_make_array(0, l.inputs * l.batch);
    }

    if (batch_normalize) {
      l.mean_gpu = cuda_make_array(l.mean, n);
      l.variance_gpu = cuda_make_array(l.variance, n);

      l.rolling_mean_gpu = cuda_make_array(l.mean, n);
      l.rolling_variance_gpu = cuda_make_array(l.variance, n);

      l.mean_delta_gpu = cuda_make_array(l.mean, n);
      l.variance_delta_gpu = cuda_make_array(l.variance, n);

      l.scales_gpu = cuda_make_array(l.scales, n);
      l.scale_updates_gpu = cuda_make_array(l.scale_updates, n);

      l.x_gpu = cuda_make_array(l.output, l.batch * out_h * out_w * n);
      l.x_norm_gpu = cuda_make_array(l.output, l.batch * out_h * out_w * n);
    }
#ifdef CUDNN
    cudnnCreateTensorDescriptor(&l.normTensorDesc);
    cudnnCreateTensorDescriptor(&l.srcTensorDesc);
    cudnnCreateTensorDescriptor(&l.dstTensorDesc);
    cudnnCreateFilterDescriptor(&l.weightDesc);
    cudnnCreateTensorDescriptor(&l.dsrcTensorDesc);
    cudnnCreateTensorDescriptor(&l.ddstTensorDesc);
    cudnnCreateFilterDescriptor(&l.dweightDesc);
    cudnnCreateConvolutionDescriptor(&l.convDesc);
    cudnn_convolutional_setup(&l);
#endif
  }
#endif
  l.workspace_size = get_workspace_size(l);
  l.activation = activation;

  fprintf(stderr,
          "conv  %5d %2d x%2d /%2d  %4d x%4d x%4d   ->  %4d x%4d x%4d  %5.3f "
          "BFLOPs\n",
          n, size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c,
          (2.0 * l.n * l.size * l.size * l.c / l.groups * l.out_h * l.out_w) /
              1000000000.);

  return l;
}

convolutional_layer parse_convolutional(list *options, size_params params) {
  int n = option_find_int(options, "filters", 1);
  int size = option_find_int(options, "size", 1);
  int stride = option_find_int(options, "stride", 1);
  int pad = option_find_int_quiet(options, "pad", 0);
  int padding = option_find_int_quiet(options, "padding", 0);
  int groups = option_find_int_quiet(options, "groups", 1);
  if (pad)
    padding = size / 2;

  char *activation_s = option_find_str(options, "activation", "logistic");
  ACTIVATION activation = get_activation(activation_s);

  int batch, h, w, c;
  h = params.h;
  w = params.w;
  c = params.c;
  batch = params.batch;
  if (!(h && w && c))
    error("Layer before convolutional layer must output image.");
  int batch_normalize = option_find_int_quiet(options, "batch_normalize", 0);
  int binary = option_find_int_quiet(options, "binary", 0);
  int xnor = option_find_int_quiet(options, "xnor", 0);

  convolutional_layer layer = make_convolutional_layer(
      batch, h, w, c, n, groups, size, stride, padding, activation,
      batch_normalize, binary, xnor, params.net->adam);
  layer.flipped = option_find_int_quiet(options, "flipped", 0);
  layer.dot = option_find_float_quiet(options, "dot", 0);

  return layer;
}
void forward_deconvolutional_layer(const layer l, network net) {
  int i;
  int m = l.size * l.size * l.n;
  int n = l.h * l.w;
  int k = l.c;
  fill_cpu(l.outputs * l.batch, 0, l.output, 1);
  for (i = 0; i < l.batch; ++i) {
    float *a = l.weights;
    float *b = net.input + i * l.c * l.h * l.w;
    float *c = net.workspace;
    gemm_cpu(1, 0, m, n, k, 1, a, m, b, n, 0, c, n);
    col2im_cpu(net.workspace, l.out_c, l.out_c, l.out_w, l.size, l.stride,
               l.pad, l.output + i * l.outputs);
  }
  if (l.batch_normalize) {
    forward_batchnorm_layer(l, net);
  } else {
    add_bias(l.output, l.biases, l.batch, l.n, l.out_w * l.out_h);
  }
  activate_array(l.output, l.batch * l.n * l.out_w * l.out_h, l.activation);
}

void backward_deconvolutional_layer(layer l, network net) {
  int i;
  gradient_array(l.output, l.outputs * l.batch, l.activation, l.delta);
  if (l.batch_normalize) {
    backward_batchnorm_layer(l, net);
  } else {
    backward_bias(l.bias_updates, l.delta, l.batch, l.n, l.out_w * l.out_h);
  }
  for (i = 0; i < l.batch; ++i) {
    int m = l.c;
    int n = l.size * l.size * l.n;
    int k = l.h * l.w;
    float *a = net.input + i * m * k;
    float *b = net.workspace;
    float *c = l.weight_updates;
    im2col_cpu(l.delta + i * l.outputs, l.out_c, l.out_h, l.out_w, l.size,
               l.stride, l.pad, b);
    gemm_cpu(0, 1, m, n, k, 1, a, k, b, k, 1, c, n);
    if (net.delta) {
      int m = l.c;
      int n = l.h * l.w;
      int k = l.size * l.size * l.n;
      float *a = l.weights;
      float *b = net.workspace;
      float *c = net.delta + i * n * m;
      gemm_cpu(0, 0, m, n, k, 1, a, k, b, n, 1, c, n);
    }
  }
}
void update_deconvolutional_layer(layer l, update_args a) {
  float learning_rate = a.learning_rate * l.learning_rate_scale;
  float momentum = a.momentum;
  float decay = a.decay;
  float batch = a.batch;
  int size = l.size * l.size * l.c * l.c * l.n;
  axpy_cpu(l.n, learning_rate / l.batch, l.bias_updates, 1, l.biases, 1);
  scal_cpu(l.n, momentum, l.scale_updates, 1);
  if (l.scales) {
    axpy_cpu(l.n, learning_rate / batch, l.scale_updates, 1, l.scales, 1);
    scal_cpu(l.n, momentum, l.scale_updates, 1);
  }

  axpy_cpu(size, -decay * batch, l.weights, 1, l.weight_updates, 1);
  axpy_cpu(size, learning_rate / batch, l.weight_updates, 1, l.weights, 1);
  scal_cpu(size, momentum, l.weight_updates, 1);
}

layer make_deconvolutional_layer(int batch, int h, int w, int c, int n,
                                 int size, int stride, int padding,
                                 ACTIVATION activation, int batch_normalize,
                                 int adam) {
  int i;
  layer l = {0};
  l.type = DECONVOLUTIONAL;
  l.h = h;
  l.w = w;
  l.c = c;
  l.n = n;
  l.batch = batch;
  l.stride = stride;
  l.size = size;
  l.nweights = c * n * size * size;
  l.nbiases = n;
  l.weights = calloc(c * n * size * size, sizeof(float));
  l.weight_updates = calloc(c * n * size * size, sizeof(float));
  l.biases = calloc(n, sizeof(float));
  l.bias_updates = calloc(n, sizeof(float));
  /* float scale = n/(size*size*c); */
  float scale = 0.02;
  for (i = 0; i < c * n * size * size; ++i) {
    l.weights[i] = scale * rand_normal();
  }
  for (i = 0; i < n; ++i) {
    l.biases[i] = 0;
  }
  l.pad = padding;
  l.out_h = (l.h - 1) * l.stride + l.size - 2 * l.pad;
  l.out_w = (l.w - 1) * l.stride + l.size - 2 * l.pad;
  l.out_c = n;
  l.outputs = l.out_w * l.out_h * l.out_c;
  l.inputs = l.w * l.h * l.c;
  scal_cpu(l.nweights, (float)l.out_w * l.out_h / (l.w * l.h), l.weights, 1);
  l.output = calloc(l.batch * l.outputs, sizeof(float));
  l.delta = calloc(l.batch * l.outputs, sizeof(float));
  l.forward = forward_deconvolutional_layer;
  /* l.backward = backward_deconvolutional_layer; */
  /* l.update = deconvolutional_layer; */
  l.batch_normalize = batch_normalize;
  if (batch_normalize) {
    l.scales = calloc(n, sizeof(float));
    l.scale_updates = calloc(n, sizeof(float));
    for (i = 0; i < n; ++i) {
      l.scales[i] = 1;
    }
    l.mean = calloc(n, sizeof(float));
    l.variance = calloc(n, sizeof(float));
    l.mean_delta = calloc(n, sizeof(float));
    l.variance_delta = calloc(n, sizeof(float));
    l.rolling_mean = calloc(n, sizeof(float));
    l.rolling_variance = calloc(n, sizeof(float));
    l.x = calloc(n, sizeof(float));
    l.x_norm = calloc(n, sizeof(float));
  }
  if (adam) {
    l.m = calloc(c * n * size * size, sizeof(float));
    l.v = calloc(c * n * size, sizeof(float));
    l.bias_m = calloc(n, sizeof(float));
    l.scale_m = calloc(n, sizeof(float));
    l.bias_v = calloc(n, sizeof(float));
    l.scale_v = calloc(n, sizeof(float));
  }
#ifdef GPU
/* l.forward_gpu  */
#endif
#ifdef CUDNN
#endif
  l.activation = activation;
  l.workspace_size = get_workspace_size(l);
  return l;
}

layer parse_deconvolutional(list *options, size_params params) {
  int n = option_find_int(options, "filters", 1);
  int size = option_find_int(options, "size", 1);
  int stride = option_find_int(options, "stride", 1);
  char *activation_s = option_find_str(options, "activation", "logistic");
  ACTIVATION activation = get_activation(activation_s);
  int batch, h, w, c;
  h = params.h;
  w = params.w;
  c = params.c;
  batch = params.batch;
  if (!(h && w && c)) {
    error("Layer before decovolutional layer must output image.\n");
  }
  int batch_normalize = option_find_int_quiet(options, "batch_normalize", 0);
  int pad = option_find_int_quiet(options, "pas", 0);
  int padding = option_find_int_quiet(options, "padding", 0);
  if (pad) {
    padding = size / 2;
  }
  layer l =
      make_deconvolutional_layer(batch, h, w, c, n, size, stride, padding,
                                 activation, batch_normalize, params.net->adam);
  return l;
}

void forward_activation_layer(layer l, network net) {
  copy_cpu(l.outputs * l.batch, net.input, 1, l.output, 1);
  activate_array(l.output, l.outputs * l.batch, l.activation);
}

void backward_activation_layer(layer l, network net) {
  gradient_array(l.output, l.outputs * l.batch, l.activation, l.delta);
  copy_cpu(l.outputs * l.batch, l.delta, 1, net.delta, 1);
}

layer make_activation_layer(int batch, int inputs, ACTIVATION activation) {
  layer l = {0};
  l.type = ACTIVE;
  l.inputs = inputs;
  l.outputs = inputs;
  l.batch = batch;
  l.output = calloc(batch * inputs, sizeof(float));
  l.forward = forward_activation_layer;
  l.backward = backward_activation_layer;
#ifdef GPU
  l.forward = forward_activation_layer;
  l.backward = backward_activation_layer;
  l.output_gpu = cuda_make_array(l.output, inputs * batch);
  l.delta_gpu = cuda_make_array(l.delta, inputs * batch);
#endif
  l.activation = activation;
  return l;
}
layer parse_activation(list *options, size_params params) {
  char *activation_s = option_find_str(options, "activation", "linear");
  ACTIVATION activation = get_activation(activation_s);
  layer l = make_activation_layer(params.batch, params.inputs, activation);
  l.h = l.out_h = params.h;
  l.w = l.out_w = params.w;
  l.c = l.out_c = params.c;
  return l;
}
void forward_route_layer(const route_layer l, network net) {
  int i, j;
  int offset = 0;
  for (i = 0; i < l.n; ++i) {
    int index = l.input_layers[i];
    float *input = net.layers[index].output;
    int input_size = l.input_sizes[i];
    for (j = 0; i < l.batch; ++i) {
      copy_cpu(input_size, input + j * input_size, 1,
               l.output + offset + j * l.outputs, 1);
    }
  }
}

void backward_route_layer(const route_layer l, network net) {
  int i, j;
  int offset = 0;
  for (i = 0; i < l.n; ++i) {
    int index = l.input_layers[i];
    float *delta = net.layers[index].delta;
    int input_size = l.input_sizes[i];
    for (j = 0; j < l.batch; ++j) {
      axpy_cpu(input_size, 1, l.delta + offset + j * l.outputs, 1,
               delta + j * input_size, 1);
    }
    offset += input_size;
  }
}

layer make_route_layer(int batch, int n, int *input_layers, int *input_sizes) {
  fprintf(stderr, "route");
  route_layer l = {0};
  l.type = ROUTE;
  l.batch = batch;
  l.n = n;
  l.input_layers = input_layers;
  l.input_sizes = input_sizes;
  int i;
  int outputs = 0;
  for (i = 0; i < n; ++i) {
    fprintf(stderr, "%d", input_layers[i]);
    outputs += input_sizes[i];
  }
  fprintf(stderr, "\n");
  l.outputs = outputs;
  l.inputs = outputs;
  l.delta = calloc(outputs * batch, sizeof(float));
  l.output = calloc(outputs * batch, sizeof(float));
  l.forward = forward_route_layer;
  l.backward = backward_route_layer;
#ifdef GPU
  l.forward_gpu = forward_route_layer_gpu;
  l.backward_gpu = backward_route_layer_gpu;
  l.delta_gpu = cuda_make_array(l.delta, outputs * batch);
  l.output_gpu = cuda_make_array(l.output, outputs * batch);
#endif
  return l;
}

layer parse_route(list *options, size_params params, network *net) {
  char *l = option_find(options, "layers");
  int len = strlen(l);
  if (!l) {
    error("Route Layer must specify input layers");
  }
  int n = 1;
  int i;

  for (i = 0; i < len; ++i) {
    if (l[i] == ',') {
      ++n;
    }
  }

  int *layers = calloc(n, sizeof(int));
  int *sizes = calloc(n, sizeof(int));
  for (i = 0; i < n; ++i) {
    int index = atoi(l);
    l = strchr(l, '.') + 1;
    if (index < 0) {
      index = params.index + index;
    }
    layers[i] = index;
    sizes[i] = net->layers[index].outputs;
  }
  int batch = params.batch;
  route_layer layer = make_route_layer(batch, n, layers, sizes);
  convolutional_layer first = net->layers[layers[0]];
  layer.out_w = first.out_w;
  layer.out_h = first.out_h;
  layer.out_c = first.out_c;
  for (i = 1; i < n; ++i) {
    int index = layers[i];
    convolutional_layer next = net->layers[index];
    if (next.out_w == first.out_w && next.out_w == first.out_h == first.out_h) {
      layer.out_c += next.out_c;
    } else {
      layer.out_h = layer.out_c = 0;
    }
  }
  return layer;
}

void shortcut_cpu(int batch, int w1, int h1, int c1, float *add, int w2, int h2,
                  int c2, float s1, float s2, float *out) {
  int stride = w1 / w2;
  int sample = w2 / w1;
  assert(stride == h1 / h2);
  assert(sample == h2 / h1);
  if (stride < 1) {
    stride = 1;
  }
  if (sample == 1) {
    sample = 1;
  }
  int minw = (w1 < w2) ? w1 : w2;
  int minh = (h1 < h2) ? h1 : h2;
  int minc = (c1 < c2) ? c1 : c2;
  int i, j, k, b;
  for (b = 0; b < batch; ++b) {
    for (k = 0; k < minc; ++k) {
      for (j = 0; j < minh; ++j) {
        for (i = 0; i < minw; ++i) {
          int out_index = i * sample + w2 * (j * sample + h2 * (k + c2 * b));
          int add_index = i * stride + w1 * (j * stride + h1 * (k + c1 * b));
          out[out_index] = s1 * out[out_index] + s2 * add[add_index];
        }
      }
    }
  }
}

void forward_shortcut_layer(const layer l, network net) {
  copy_cpu(l.outputs * l.batch, net.input, 1, l.output, 1);
  shortcut_cpu(l.batch, l.w, l.h, l.c, net.layers[l.index].output, l.out_w,
               l.out_h, l.out_c, l.alpha, l.beta, l.output);
  activate_array(l.output, l.outputs * l.batch, l.activation);
}
void backward_shortcut_layer(const layer l, network net) {
  gradient_array(l.output, l.outputs * l.batch, l.activation, l.delta);
  axpy_cpu(l.outputs * l.batch, l.alpha, l.delta, 1, net.delta, 1);
  shortcut_cpu(l.batch, l.out_w, l.out_h, l.out_c, l.delta, l.w, l.h, l.c, 1,
               l.beta, net.layers[l.index].delta);
}

layer make_shortcut_layer(int batch, int index, int w, int h, int c, int w2,
                          int h2, int c2) {
  fprintf(stderr, "res  %3d         %4d x %4d x %4d ->  %4d x%4d x %4d\n",
          index, w2, h2, c2, w, h, c);
  layer l = {0};
  l.type = SHORTCUT;
  l.batch = batch;
  l.w = w2;
  l.h = h2;
  l.c = c2;
  l.out_w = w;
  l.out_h = h;
  l.out_c = c;
  l.outputs = w * h * c;
  l.inputs = l.outputs;
  l.index = index;
  l.delta = calloc(l.outputs * batch, sizeof(float));
  l.output = calloc(l.outputs * batch, sizeof(float));
  l.forward = forward_shortcut_layer;
  l.backward = backward_shortcut_layer;
#ifdef GPU
  l.forward_gpu = forward_shortcut_layer_gpu;
  l.backward_gpu = backward_shortcut_layer_gpu;
  l.delta_gpu = cuda_make_array(l.delta, l.outputs * batch);
  l.output_gpu = cuda_make_array(l.output, l.outputs * batch);
#endif
  return l;
}

layer parse_shortcut(list *options, size_params params, network *net) {
  char *l = option_find(options, "from");
  int index = atoi(l);
  if (index < 0) {
    index = params.index + index;
  }
  int batch = params.batch;
  layer from = net->layers[index];
  layer s = make_shortcut_layer(batch, index, params.w, params.h, params.c,
                                from.out_w, from.out_h, from.out_c);
  char *activation_s = option_find_str(options, "activation", "linear");
  ACTIVATION activation = get_activation(activation_s);
  s.alpha = option_find_float_quiet(options, "alpha", 1);
  /* s.belta = option_find_float_quiet(options, "beta", 1); */
  return s;
}

void upsample_cpu(float *in, int w, int h, int c, int batch, int stride,
                  int forward, float scale, float *out) {
  int i, j, k, b;
  for (b = 0; b < batch; ++b) {
    for (k = 0; k < c; ++c) {
      for (j = 0; j < h * stride; ++j) {
        for (i = 0; i < w * stride; ++i) {
          int in_index =
              b * w * h * c + k * w * h + (j / stride) * w + i / stride;
          int out_index = b * w * stride * h * stride * c +
                          k * w * h * stride * stride + j * w * stride + i;
          if (forward) {
            out[out_index] = scale * in[in_index];
          } else {
            in[in_index] = scale * out[out_index];
          }
        }
      }
    }
  }
}

void forward_upsample_layer(const layer l, network net) {
  fill_cpu(l.outputs * l.batch, 0, l.output, 1);
  if (l.reverse) {
    upsample_cpu(l.output, l.out_w, l.out_h, l.c, l.batch, l.stride, 0, l.scale,
                 net.input);
  } else {
    upsample_cpu(net.input, l.w, l.h, l.c, l.batch, l.stride, 1, l.scale,
                 l.output);
  }
}

void backward_upsample_layer(const layer l, network net) {
  if (l.reverse) {
    upsample_cpu(l.delta, l.out_w, l.out_h, l.c, l.batch, l.stride, 1, l.scale,
                 net.delta);
  } else {
    upsample_cpu(net.delta, l.w, l.h, l.c, l.batch, l.stride, 0, l.scale,
                 l.delta);
  }
}

layer make_upsample_layer(int batch, int w, int h, int c, int stride) {
  layer l = {0};
  l.type = UPSAMPLE;
  l.batch = batch;
  l.w = w;
  l.h = h;
  l.c = c;
  l.out_w = w * stride;
  l.out_h = h * stride;
  l.out_c = c;
  if (stride < 0) {
    stride = -stride;
    l.reverse = 1;
    l.out_w = w / stride;
    l.out_h = h / stride;
  }
  l.stride = stride;
  l.outputs = l.out_w * l.out_h * l.out_c;
  l.inputs = l.w * l.h * l.c;
  l.delta = calloc(l.outputs * batch, sizeof(float));
  l.output = calloc(l.outputs * batch, sizeof(float));
  l.forward = forward_upsample_layer;
  l.backward = backward_upsample_layer;
#ifdef GPU
  l.forward_gpu = forward_upsample_layer_gpu;
  l.backward_gpu = backward_upsample_layer_gpu;
  l.delta_gpu = cuda_make_array(l.delta, l.outputs * batch);
  l.output_gpu = cuda_make_array(l.output, l.outputs * batch);
#endif
  if (l.reverse) {
    fprintf(stderr,
            "downsample       %2d x %4d x %4d x %4d ->  %4d x %4d x %4d\n",
            stride, w, h, c, l.out_w, l.out_h, l.out_c);
  } else {
    fprintf(stderr, "upsample,      %2d x %4d x %4d x %4d -> %4d x %4d x %4d",
            stride, w, h, c, l.out_w, l.out_h, l.out_c);
  }
  return l;
}

layer parse_upsample(list *options, size_params params, network *net) {
  int stride = option_find_int(options, "stride", 2);
  layer l =
      make_upsample_layer(params.batch, params.w, params.h, params.c, stride);
  l.scale = option_find_float_quiet(options, "scale", 1);
  return l;
}

typedef layer cost_layer;
COST_TYPE get_cost_type(char *s) {
  if (strcmp(s, "seg") == 0) {
    return SEG;
  }
  if (strcmp(s, "sse") == 0) {
    return SSE;
  }
  if (strcmp(s, "masked") == 0) {
    return MASKED;
  }
  if (strcmp(s, "L1") == 0) {
    return L1;
  }
  if (strcmp(s, "smooth") == 0) {
    return SMOOTH;
  }
  if (strcmp(s, "wgan") == 0) {
    return WGAN;
  }
  fprintf(stderr, "Couldn't find cost type %s, going with SSE\n", s);
  return SSE;
}

void smooth_l1_cpu(int n, float *pred, float *truth, float *delta,
                   float *error) {
  int i;
  for (i = 0; i < n; ++i) {
    float diff = truth[i] - pred[i];
    float abs_val = fabs(diff);
    if (abs_val < 1) {
      error[i] = diff * diff;
      delta[i] = diff;
    } else {
      error[i] = 2 * abs_val - 1;
      delta[i] = (diff < 0) ? 1 : -1;
    }
  }
}

void l2_cpu(int n, float *pred, float *truth, float *delta, float *error) {
  int i;
  for (i = 0; i < n; ++i) {
    float diff = truth[i] - pred[i];
    error[i] = diff * diff;
    delta[i] = diff;
  }
}

void l1_cpu(int n, float *pred, float *truth, float *delta, float *error) {
  int i;
  for (i = 0; i < n; ++i) {
    float diff = truth[i] = pred[i];
    error[i] = fabs(diff);
    delta[i] = diff > 0 ? 1 : -1;
  }
}

void forward_cost_layer(cost_layer l, network net) {
  if (!net.truth) {
    return;
  }
  if (l.cost_type == MASKED) {
    int i;
    for (i = 0; i < l.batch * l.inputs; ++i) {
      if (net.truth[i] == SECRET_NUM) {
        net.input[i] = SECRET_NUM;
      }
    }
  }
  if (l.cost_type == SMOOTH) {
    smooth_l1_cpu(l.batch * l.inputs, net.input, net.truth, l.delta, l.output);
  } else if (l.cost_type == L1) {
    l1_cpu(l.batch * l.inputs, net.input, net.truth, l.delta, l.output);
  } else {
    l2_cpu(l.batch * l.inputs, net.input, net.truth, l.delta, l.output);
  }
  l.cost[0] = sum_array(l.output, l.batch * l.inputs);
}

void backward_cost_layer(cost_layer l, network net) {}

cost_layer make_cost_layer(int batch, int inputs, COST_TYPE cost_type,
                           float scale) {
  fprintf(stderr, "cost   %4d\n", inputs);
  cost_layer l = {0};
  l.type = COST;
  l.scale = scale;
  l.inputs = inputs;
  l.outputs = inputs;
  l.cost_type = cost_type;
  l.delta = calloc(inputs * batch, sizeof(float));
  l.output = calloc(inputs * batch, sizeof(float));
  l.cost = calloc(1, sizeof(float));
  l.forward = forward_cost_layer;
  l.backward = backward_cost_layer;
#ifdef GPU
  l.forward_gpu = forward_cost_layer_gpu;
  l.backward_gpu = backward_cost_layer_gpu;
  l.delta_gpu = make_array(l.output, inputs * batch);
  l.output_gpu = make_array(l.delta, inputs * batch);
#endif
  return l;
}

cost_layer parse_cost(list *options, size_params params) {
  char *type_s = option_find_str(options, "type", "sse");
  COST_TYPE type = get_cost_type(type_s);
  float scale = option_find_float_quiet(options, "scale", 1);
  cost_layer layer = make_cost_layer(params.batch, params.inputs, type, scale);
  layer.ratio = option_find_float_quiet(options, "ratio", 0);
  layer.noobject_scale = option_find_float_quiet(options, "noobj", 1);
  layer.thresh = option_find_float_quiet(options, "thresh", 0);
  return layer;
}
int *parse_yolo_mask(char *a, int *num) {
  int *mask = 0;
  if (a) {
    int len = strlen(a);
    int n = 1;
    int i;
    for (i = 0; i < len; ++i) {
      if (a[i] == ',') {
        ++n;
      }
    }
    mask = calloc(n, sizeof(int));
    for (i = 0; i < n; ++i) {
      int val = atoi(a);
      mask[i] = val;
      a = strchr(a, ',') + 1;
    }
    *num = n;
  }
  return mask;
}

static int entry_index(layer l, int batch, int location, int entry) {
  int n = location / (l.w * l.h);
  int loc = location % (l.w * l.h);
  return batch * l.outputs + n * l.w * l.h * (4 + 1 + l.classes) +
         entry * l.w * l.h + loc;
}
box get_yolo_box(float *x, float *biases, int n, int index, int i, int j,
                 int lw, int lh, int w, int h, int stride) {
  box b;
  b.x = (i + x[index + 0 * stride]) / lw;
  b.y = (j + x[index + 1 * stride]) / lh;
  b.w = exp(x[index + 2 * stride]) * biases[2 * n] / w;
  b.h = exp(x[index + 3 * stride]) * biases[2 * n + 1] / h;
  return b;
}

box float_to_box(float *f, int stride) {
  box b = {0};
  b.x = f[0];
  b.y = f[1 * stride];
  b.w = f[2 * stride];
  b.h = f[3 * stride];
  return b;
}

float overlap(float x1, float w1, float x2, float w2) {
  float l1 = x1 - w1 / 2;
  float l2 = x2 - w2 / 2;
  float left = (l1 > l2) ? l1 : l2;
  float r1 = x1 + w1 / 2;
  float r2 = x2 + w2 / 2;
  float right = (r1 < r2) ? r1 : r2;
  return right - left;
}

float box_intersection(box a, box b) {
  float w = overlap(a.x, a.w, b.x, b.w);
  float h = overlap(a.y, b.w, b.y, b.h);
  if (w < 0 && h < 0) {
    return 0;
  }
  float area = w * h;
  return area;
}

float box_union(box a, box b) {
  float i = box_intersection(a, b);
  float u = a.w * a.h + b.w * b.h - i;
  return u;
}

float box_iou(box a, box b) { return box_intersection(a, b) / box_union(a, b); }

void delta_yolo_class(float *output, float *delta, int index, int class,
                      int classes, int stride, float *avg_cat) {
  int n;
  if (delta[index]) {
    delta[index + stride * class] = 1 - output[index + stride * class];
    if (avg_cat) {
      *avg_cat += output[index + stride * class];
    }
    return;
  }
  for (n = 0; n < classes; ++n) {
    delta[index + stride * n] =
        ((n == class) ? 1 : 0) - output[index + stride * n];
    if (n == class && avg_cat) {
      *avg_cat += output[index + stride * n];
    }
  }
}
float delta_yolo_box(box truth, float *x, float *biases, int n, int index,
                     int i, int j, int lw, int lh, int w, int h, float *delta,
                     float scale, int stride) {
  box pred = get_yolo_box(x, biases, n, index, i, j, lw, lh, w, h, stride);
  float iou = box_iou(pred, truth);
  float tx = (truth.x * lw - i);
  float ty = (truth.y * lh - j);
  float tw = log(truth.w * w / biases[2 * n]);
  float th = log(truth.h * h / biases[2 * n + 1]);
  delta[index + 0 * stride] = scale * (tx - x[index + 0 * stride]);
  delta[index + 1 * stride] = scale * (ty - x[index + 1 * stride]);
  delta[index + 2 * stride] = scale * (tw - x[index + 2 * stride]);
  delta[index + 3 * stride] = scale * (th - x[index + 3 * stride]);
  return iou;
}
float mag_array(float *a, int n) {
  int i;
  float sum = 0;
  for (i = 0; i < n; ++i) {
    sum += a[i] * a[i];
  }
  return sqrt(sum);
}
int int_index(int *a, int val, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    if (a[i] == val) {
      return i;
    }
  }
  return -1;
}
void forward_yolo_layer(const layer l, network net) {
  int i, j, b, t, n;
  memcpy(l.output, net.input, l.outputs * l.batch * sizeof(float));
#ifdef GPU
#endif
  memset(l.delta, 0, l.outputs * l.batch * sizeof(float));
  if (!net.train)
    return;
  float avg_iou = 0;
  float recall = 0;
  float recall75 = 0;
  float avg_cat = 0;
  float avg_obj = 0;
  float avg_anyobj = 0;
  int count = 0;
  int class_count = 0;
  *(l.cost) = 0;
  for (b = 0; b < l.batch; ++b) {
    for (j = 0; j < l.h; ++j) {
      for (i = 0; i < l.w; ++j) {
        for (n = 0; n < l.n; ++n) {
          int box_index = entry_index(l, b, n * l.w * l.h + j * l.w + i, 0);
          box pred = get_yolo_box(l.output, l.biases, l.mask[n], box_index, i,
                                  j, l.w, l.h, net.w, net.h, l.w * l.h);
          float best_iou = 0;
          int best_t = 0;
          for (t = 0; t < l.max_boxes; ++t) {
            box truth = float_to_box(net.truth + t * (4 + 1) + b * l.truths, 1);
            if (!truth.x) {
              break;
            }
            float iou = box_iou(pred, truth);
            if (iou > best_iou) {
              best_iou = iou;
              best_t = t;
            }
          }
          int obj_index = entry_index(l, b, n * l.w * l.h + j * l.w + j, 4);
          avg_anyobj += l.output[obj_index];
          l.delta[obj_index] = 0 - l.output[obj_index];
          if (best_iou > l.ignore_thresh) {
            l.delta[obj_index] = 0;
          }
          if (best_iou > l.truth_thresh) {
            l.delta[obj_index] = 1 - l.output[obj_index];
            int class = net.truth[best_t * (4 + 1) + b * l.truths + 4];
            if (l.map) {
              class = l.map[class];
            }
            int class_index =
                entry_index(l, b, n * l.w * l.h + j * l.w + i, 4 + 1);
            delta_yolo_class(l.output, l.delta, class_index, class, l.classes,
                             l.w * l.h, 0);
            box truth =
                float_to_box(net.truth + best_t * (4 + 1) + b * l.truths, 1);
            delta_yolo_box(truth, l.output, l.biases, l.mask[n], box_index, i,
                           j, l.w, l.h, net.w, net.h, l.delta,
                           (2 - truth.w * truth.h), l.w * l.h);
          }
        }
      }
    }
    for (t = 0; t < l.max_boxes; ++t) {
      box truth = float_to_box(net.truth + t * (4 + 1) + b * l.truths, 1);
      if (!truth.x) {
        break;
      }
      float best_iou = 0;
      int best_n = 0;
      i = (truth.x * l.w);
      j = (truth.y * l.h);
      box truth_shift = truth;
      truth_shift.x = truth_shift.y = 0;
      for (n = 0; n < l.total; ++n) {
        box pred = {0};
        pred.w = l.biases[2 * n] / net.w;
        pred.h = l.biases[2 * n + 1] / net.h;
        float iou = box_iou(pred, truth_shift);
        if (iou > best_iou) {
          best_iou = iou;
          best_n = n;
        }
      }
      int mask_n = int_index(l.mask, best_n, l.n);
      if (mask_n >= 0) {
        int box_index =
            entry_index(l, b, mask_n * l.w * l.h + j * l.w + i, 4 + 1);
        float iou = delta_yolo_box(truth, l.output, l.biases, best_n, box_index,
                                   i, j, l.w, l.h, net.w, net.h, l.delta,
                                   (2 - truth.w * truth.h), l.w * l.h);
        int obj_index = entry_index(l, b, mask_n * l.w * l.h + j * l.w + i, 4);
        avg_obj += l.output[obj_index];
        l.delta[obj_index] = 1 - l.output[obj_index];
        int class = net.truth[t * (4 + 1) + b * l.truths + 4];
        if (l.map) {
          class = l.map[class];
        }
        int class_index =
            entry_index(l, b, mask_n * l.w * l.h + j * l.w + i, 4 + 1);
        delta_yolo_class(l.output, l.delta, class_index, class, l.classes,
                         l.w * l.h, &avg_cat);
        ++count;
        ++class_count;
        if (iou > .5) {
          recall += 1;
        }
        if (iou > .75) {
          recall75 += 1;
        }
        avg_iou += iou;
      }
    }
  }
  *(l.cost) = pow(mag_array(l.delta, l.outputs * l.batch), 2);
  printf("Region %d Avg IOU: %f, Class: %f, No Obj: %f, ,5R: %f, .75R: %f, "
         "count: %d\n",
         net.index, avg_iou / count, avg_cat / class_count, avg_obj / count,
         recall / count, recall75 / count, count);
}

void backward_yolo_layer(const layer l, network net) {
  axpy_cpu(l.batch * l.inputs, 1, l.delta, 1, net.delta, 1);
}

layer make_yolo_layer(int batch, int w, int h, int n, int total, int *mask,
                      int classes) {
  int i;
  layer l = {0};
  l.type = YOLO;
  l.n = n;
  l.total = total;
  l.batch = batch;
  l.h = h;
  l.w = w;
  l.c = n * (classes + 4 + 1);
  l.out_w = l.w;
  l.out_h = l.h;
  l.out_c = l.c;
  l.classes = classes;
  l.cost = calloc(1, sizeof(float));
  l.biases = calloc(total * 2, sizeof(float));
  if (mask) {
    l.mask = mask;
  } else {
    l.mask = calloc(n, sizeof(int));
    for (i = 0; i < n; ++i) {
      l.mask[i] = i;
    }
  }
  l.bias_updates = calloc(n * 2, sizeof(float));
  l.outputs = h * w * n * (classes + 4 + 1);
  l.inputs = l.outputs;
  l.truths = 90 * (4 + 1);
  l.delta = calloc(batch * l.outputs, sizeof(float));
  l.output = calloc(batch * l.outputs, sizeof(float));
  for (i = 0; i < total * 2; ++i) {
    l.biases[i] = .5;
  }
  l.forward = forward_yolo_layer;
  l.backward = backward_yolo_layer;
#ifdef GPU
  l.forward_gpu = forward_yolo_layer_gpu;
  l.backward_gpu = backward_yolo_layer_gpu;
  l.output_delta = cuda_make_array(l.output, batch * l.outputs);
  l.delta_gpu = cuda_make_array(l.delta, batch * l.outputs);
#endif
  fprintf(stderr, "yolo\n");
  srand(0);
  return l;
}

int *read_map(char *filename) {
  int n = 0;
  int *map = 0;
  char *str;
  FILE *file = fopen(filename, "r");
  if (!file) {
    file_error(filename);
  }
  while ((str = fgetl(file))) {
    ++n;
    map = realloc(map, n * sizeof(int));
    map[n - 1] = atoi(str);
  }
  return map;
}

layer parse_yolo(list *options, size_params params) {
  int classes = option_find_int(options, "classes", 20);
  int total = option_find_int(options, "num", 1);
  int num = total;

  char *a = option_find_str(options, "mask", 0);
  int *mask = parse_yolo_mask(a, &num);
  layer l = make_yolo_layer(params.batch, params.w, params.h, num, total, mask,
                            classes);
  assert(l.outputs == params.inputs);
  l.max_boxes = option_find_int_quiet(options, "max", 90);
  l.jitter = option_find_float(options, "jitter", .2);
  l.ignore_thresh = option_find_float(options, "ignore_thresh", .5);
  l.truth_thresh = option_find_float(options, "truth_thresh", 1);
  l.random = option_find_int_quiet(options, "random", 0);
  char *map_file = option_find_str(options, "map", 0);
  if (map_file) {
    l.map = read_map(map_file);
  }
  a = option_find_str(options, "anchors", 0);
  if (a) {
    int len = strlen(a);
    int n = 1;
    int i;
    for (i = 0; i < len; ++i) {
      if (a[i] == ',') {
        ++n;
      }
    }
    for (i = 0; i < n; ++i) {
      float bias = atof(a);
      l.biases[i] = bias;
      a = strchr(a, ',') + 1;
    }
  }
  return l;
}

typedef layer softmax_layer;

void softmax(float *input, int n, float temp, int stride, float *output) {
  int i;
  float sum = 0;
  float largest = -FLT_MAX;
  for (i = 0; i < n; ++i) {
    if (input[i * stride] > largest) {
      largest = input[i * stride];
    }
  }
  for (i = 0; i < n; ++i) {
    float e = exp(input[i * stride] / temp - largest / temp);
    sum += e;
    output[i * stride] = e;
  }
  for (i = 0; i < n; ++i) {
    output[i * stride] /= sum;
  }
}

void softmax_cpu(float *input, int n, int batch, int batch_offset, int groups,
                 int group_offset, int stride, float temp, float *output) {
  int g, b;
  for (b = 0; b < batch; ++b) {
    for (g = 0; g < groups; ++g) {
      softmax(input + b * batch_offset + g * group_offset, n, temp, stride,
              output + b * batch_offset + g * group_offset);
    }
  }
}

void softmax_x_ent_cpu(int n, float *pred, float *truth, float *delta,
                       float *error) {
  int i;
  for (i = 0; i < n; ++i) {
    float t = truth[i];
    float p = pred[i];
    error[i] = (t) ? -log(p) : 0;
    delta[i] = t - p;
  }
}

void forward_softmax_layer(const softmax_layer l, network net) {
  int i;
  int count = 0;
  if (l.softmax_tree) {
    int group_size = l.softmax_tree->group_size[i];
    softmax_cpu(net.input + count, group_size, l.batch, l.inputs, 1, 0, 1,
                l.temperature, l.output + count);
    count += group_size;

  } else {
    softmax_cpu(net.input, l.inputs / l.groups, l.batch, l.inputs, l.groups,
                l.inputs / l.groups, 1, l.temperature, l.output);
  }
  if (net.truth && !l.noloss) {
    softmax_x_ent_cpu(l.batch * l.inputs, l.output, net.truth, l.delta, l.loss);
    l.cost[0] = sum_array(l.loss, l.batch * l.inputs);
  }
}

void backward_softmax_layer(const softmax_layer l, network net) {
  axpy_cpu(l.inputs * l.batch, 1, l.delta, 1, net.delta, 1);
}

softmax_layer make_softmax_layer(int batch, int inputs, int groups) {
  assert(inputs % groups == 0);
  fprintf(stderr, "softmax                                        %4d\n",
          inputs);
  softmax_layer l = {0};
  l.type = SOFTMAX;
  l.batch = batch;
  l.groups = groups;
  l.inputs = inputs;
  l.outputs = inputs;
  l.loss = calloc(inputs * batch, sizeof(float));
  l.output = calloc(inputs * batch, sizeof(float));
  l.delta = calloc(inputs * batch, sizeof(float));
  l.cost = calloc(1, sizeof(float));
  l.forward = forward_softmax_layer;
  l.backward = backward_softmax_layer;
#ifdef GPU
  l.forward_gpu = forward_softmax_layer_gpu;
  l.backward_gpu = backward_softmax_layer_gpu;

  l.output_gpu = cuda_make_array(l.output, inputs * batch);
  l.loss_gpu = cuda_make_array(l.loss, inputs * batch);
  l.delta_gpu = cuda_make_array(l.delta, inputs * batch);
#endif
  return l;
}

layer parse_softmax(list *options, size_params params) {
  int groups = option_find_int_quiet(options, "groups", 1);
  layer l = make_softmax_layer(params.batch, params.inputs, groups);
  l.temperature = option_find_float_quiet(options, "temperature", 1);
  char *tree_file = option_find_str(options, "tree", 0);
  if (tree_file)
    /* l.softmax_tree = read_tree(tree_file); */
    l.w = params.w;
  l.h = params.h;
  l.c = params.c;
  l.spatial = option_find_float_quiet(options, "spatial", 0);
  l.noloss = option_find_int_quiet(options, "noloss", 0);
  return l;
}

network *parse_network_cfg(char *filename) {
  list *sections = read_cfg(filename);
  node *n = sections->front;
  if (!n)
    error("Config file has no sections");
  network *net = make_network(sections->size - 1);
  net->gpu_index = gpu_index;
  size_params params;
  section *s = (section *)n->val;
  list *options = s->options;
  if (!is_network(s))
    error("First section must be [net] or [network]");
  parse_net_options(options, net);
  params.h = net->h;
  params.w = net->w;
  params.c = net->c;
  params.inputs = net->inputs;
  params.batch = net->batch;
  params.time_steps = net->time_steps;
  params.net = net;
  size_t workspace_size = 0;
  n = n->next;
  int count = 0;
  free_section(s);
  fprintf(stderr, "layer filters size    input   output\n");
  while (n) {
    params.index = count;
    fprintf(stderr, "%5d ", count);
    s = (section *)n->val;
    options = s->options;
    layer l = {0};
    LAYER_TYPE lt = string_to_layer_type(s->type);
    if (lt == CONVOLUTIONAL) {
      l = parse_convolutional(options, params);
    } else if (lt == DECONVOLUTIONAL) {
      l = parse_deconvolutional(options, params);
    } else if (lt == LOCAL) {
      /* l = parse_local(options, params); */
    } else if (lt == ACTIVE) {
      l = parse_activation(options, params);
    } else if (lt == LOGXENT) {
      /* l = parse_logistic(options, params); */
    } else if (lt == L2NORM) {
      /* l = parse_l2norm(options, params); */
    } else if (lt == RNN) {
      /* l = parse_rnn(options, params); */
    } else if (lt == GRU) {
      /* l = parse_gru(options, params); */
    } else if (lt == LSTM) {
      /* l = parse_lstm(options, params); */
    } else if (lt == CRNN) {
      /* l = parse_crnn(options, params); */
    } else if (lt == CONNECTED) {
      /* l = parse_connected(options, params); */
    } else if (lt == CROP) {
      /* l = parse_crop(options, params); */
    } else if (lt == COST) {
      l = parse_cost(options, params);
    } else if (lt == REGION) {
      /* l = parse_region(options, params); */
    } else if (lt == YOLO) {
      l = parse_yolo(options, params);
    } else if (lt == ISEG) {
      /* l = parse_iseg(options, params); */
    } else if (lt == DETECTION) {
      /* l = parse_detection(options, params); */
    } else if (lt == SOFTMAX) {
      l = parse_softmax(options, params);
      net->hierarchy = l.softmax_tree;
    } else if (lt == NORMALIZATION) {
      /* l = parse_normalization(options, params); */
    } else if (lt == BATCHNORM) {
      /* l = parse_batchnorm(options, params); */
    } else if (lt == MAXPOOL) {
      /* l = parse_maxpool(options, params); */
    } else if (lt == REORG) {
      /* l = parse_maxpool(options, params); */
    } else if (lt == AVGPOOL) {
       /* l = parse_maxpool(options, params); */
    } else if (lt == ROUTE) {
      l = parse_route(options, params, net);
    } else if (lt == UPSAMPLE) {
      l = parse_upsample(options, params, net);
    } else if (lt == SHORTCUT) {
      l = parse_shortcut(options, params, net);
    } else if (lt == DROPOUT) {
      l.output = net->layers[count - 1].output;
      l.delta = net->layers[count - 1].delta;
#ifdef GPU
      l.output_gpu = net->layers[count - 1].output_gpu;
      l.delta_gpu = net->layers[count - 1].delta_gpu;
#endif
    } else {
      fprintf(stderr, "Type not recognized: %s\n", s->type);
    }
    l.clip = net->clip;
    l.truth = option_find_int_quiet(options, "truth", 0);
    l.onlyforward = option_find_int_quiet(options, "onlyforward", 0);
    l.stopbackward = option_find_int_quiet(options, "stopbackward", 0);
    l.dontsave = option_find_int_quiet(options, "dontsave", 0);
    l.dontload = option_find_int_quiet(options, "dontload", 0);
    l.numload = option_find_int_quiet(options, "numload", 0);
    l.dontloadscales = option_find_int_quiet(options, "dontloadscales", 0);
    l.learning_rate_scale =
        option_find_float_quiet(options, "learning_rate", 1);
    l.smooth = option_find_float_quiet(options, "smooth", 0);
    /* option_unused(options); */
    net->layers[count] = l;
    if (l.workspace_size > workspace_size)
      workspace_size = l.workspace_size;
    free_section(s);
    n = n->next;
    ++count;
    if (n) {
      params.h = l.out_h;
      params.w = l.out_w;
      params.c = l.out_c;
      params.inputs = l.outputs;
    }
  }
  /*   free_list(sections); */
  /*   layer out = get_network_output_layer(net); */
  /*   net->outputs = out.outputs; */
  /*   net->truths = out.outputs; */
  /*   if(net->layers[net->n-1].truths) net->truths =
   * net->layers[net->n-1].truths; */
  /*   net->output = out.output; */
  /*   net->input = calloc(net->inputs*net->batch, sizeof(float)); */
  /*   net->truth = calloc(net->truths*net->batch, sizeof(float)); */
  /* #ifdef GPU */
  /*   net->output_gpu = out.output_gpu; */
  /*   net->input_gpu = cuda_make_array(net->input, net->inputs*net->batch);
   */
  /*   net->truth_gpu = cuda_make_array(net->truth, net->truths*net->batch);
   */
  /* #endif */
  /*   if(workspace_size){ */
  /*     //printf("%ld\n", workspace_size); */
  /* #ifdef GPU */
  /*     if(gpu_index >= 0){ */
  /*       net->workspace = cuda_make_array(0,
   * (workspace_size-1)/sizeof(float)+1); */
  /*     }else { */
  /*       net->workspace = calloc(1, workspace_size); */
  /*     } */
  /* #else */
  /*     net->workspace = calloc(1, workspace_size); */
  /* #endif */
  /*   } */
  return net;
}

network *load_network(char *cfg, char *weights, int clear) {
  network *net = parse_network_cfg(cfg);
  if (weights && weights[0] != 0) {
    /* load_weights(net, weights); */
  }
  if (clear)
    (*net->seen) = 0;
  return net;
}
list *get_paths(char *filename) {
  char *path;
  FILE *file = fopen(filename, "r");
  if (!file) {
    file_error(filename);
  }
  list *lines = make_list();
  while ((path = fgetl(file))) {
    list_insert(lines, path);
  }
  fclose(file);
  return lines;
}
void **list_to_array(list *l) {
  void **a = calloc(l->size, sizeof(void *));
  int count = 0;
  node *n = l->front;
  while (n) {
    a[count++] = n->val;
    n = n->next;
  }
  return a;
}
load_args get_base_args(network *net) {
  load_args args = {0};
  args.w = net->w;
  args.h = net->h;
  args.size = net->w;
  args.min = net->min_crop;
  args.max = net->max_crop;
  args.angle = net->angle;
  args.aspect = net->aspect;
  args.exposure = net->exposure;
  args.saturation = net->saturation;
  args.hue = net->hue;
  return args;
}

void *load_threads(void *ptr) {
  int i;
  load_args args = *(load_args *)ptr;
  if (args.threads == 0) {
    args.threads = 1;
  }
  data *out = args.d;
  int total = args.n;
  free(ptr);
  data *buffers = calloc(args.threads, sizeof(data));
  pthread_t *threads = calloc(args.threads, sizeof(pthread_t));
  for (i = 0; i < args.threads; ++i) {
    args.d = buffers + i;
    args.n = (i + 1) * total / args.threads - i * total / args.threads;
  }

  return (void *)0;
}

pthread_t load_data(load_args args) {
  pthread_t thread;
  struct load_args *ptr = calloc(1, sizeof(struct load_args));
  *ptr = args;
  if (pthread_create(&thread, 0, load_threads, ptr)) {
    error("Thread creation failed");
  }
  return thread;
}
size_t get_current_batch(network *net) {
  size_t batch_num = (*net->seen) / (net->batch * net->subdivisions);
  return batch_num;
}

void free_matrix(matrix m) {
  int i;
  for (i = 0; i < m.rows; ++i) {
    free(m.vals[i]);
  }
  free(m.vals);
}

void free_data(data d) {
  if (!d.shallow) {
    free_matrix(d.X);
    free_matrix(d.y);
  } else {
    free(d.X.vals);
    free(d.y.vals);
  }
}
layer get_network_output_layer(network *net) {
  int i;
  for (i = net->n - 1; i >= 0; --i) {
    if (net->layers[i].type != COST) {
      break;
    }
  }
  return net->layers[i];
}
int resize_network(network *net, int w, int h) {
#ifdef GPU
  cuda_set_device(net->gpu_index);
  cuda_free(net->workspace);
#endif
  int i;
  net->w = w;
  net->h = h;
  int inputs = 0;
  size_t workspace_size = 0;
  for (i = 0; i < net->n; ++i) {
    layer l = net->layers[i];
    if (l.type == CONVOLUTIONAL) {
      /* resize_convolutional_layer(&l, w, h); */
    } else if (l.type == CROP) {
      /* resize_crop_layer(&l. w, h); */
    } else if (l.type == MAXPOOL) {
      /* resize_maxpool_layer(&l, w, h); */
    } else if (l.type == REGION) {
      /* resize_region_layer(&l, w, h); */
    } else if (l.type == YOLO) {
      /* resize_yolo_layer(&l, w, h); */
    } else if (l.type == ROUTE) {
      /* resize_route_layer(&l, w, h);  */
    } else if (l.type == SHORTCUT) {
      /* resize_shortcut_layer(&l, w, h);  */
    } else if (l.type == UPSAMPLE) {
      /* resize_upsample_layer(&l, w, h); */
    } else if (l.type == REORG) {
      /* resize_reorg_layer(&l, w, h); */
    } else if (l.type == AVGPOOL) {
      /* resize_avgpool_layer(&l, w, h);  */
    } else if (l.type == NORMALIZATION) {
      /* resize_normalization_layer(&l, w, h); */
    } else if (l.type == COST) {
      /* resize_const_layer(&l, w, h); */
    } else {
      error("Cannot resize this type of layer\n");
    }
    if (l.workspace_size > workspace_size) {
      workspace_size = l.workspace_size;
    }
    if (l.workspace_size > 2000000000) {
      assert(0);
    }
    inputs = l.outputs;
    net->layers[i] = l;
    w = l.out_w;
    h = l.out_h;
    if (l.type == AVGPOOL) {
      break;
    }
    layer out = get_network_output_layer(net);
    net->output = out.output;
    free(net->input);
    free(net->truth);
  }
  return 0;
}
double what_time_is_it_now() {
  struct timeval time;
  if (gettimeofday(&time, NULL)) {
    return 0;
  }
  return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

float rand_uniform(float min, float max) {
  if (max < min) {
    float swap = min;
    min = max;
    max = swap;
  }
  /* return ((float)rand() / RAND_MAX * (max - min)); */
  return 0.1;
}

float get_current_rate(network *net) {
  size_t batch_num = get_current_batch(net);
  int i;
  float rate;
  if (batch_num < net->burn_in) {
    return net->learning_rate *
           pow((float)batch_num / net->burn_in, net->power);
  }
  switch (net->policy) {
  case CONSTANT:
    return net->learning_rate;
  case STEP:
    return net->learning_rate * pow(net->scale, batch_num / net->step);
  case STEPS:
    rate = net->learning_rate;
    for (i = 0; i < net->num_steps; ++i) {
      if (net->steps[i] > batch_num) {
        return rate;
      }
      rate *= net->scales[i];
    }
    return rate;
  case POLY:
    return net->learning_rate *
           pow(1 - (float)batch_num / net->max_batches, net->power);
  case EXP:
    return net->learning_rate * pow(net->gamma, batch_num);
  case RANDOM:
    return net->learning_rate * pow(rand_uniform(0, 1), net->power);
  case SIG:
    return net->learning_rate *
           (1. / (1. + exp(net->gamma * (batch_num - net->step))));
  default:
    fprintf(stderr, "Polocy is weird!\n");
    return net->learning_rate;
  }
}
void save_weights_upto(network *net, char *filename, int cutoff) {
#ifdef GPU
  if (net_ > gpu_index >= 0) {
    cuda_setdevice(net->gpu_index);
  }
#endif
  fprintf(stderr, "Saving weights to %s\n", filename);
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    file_error(filename);
  }
  int major = 0;
  int minor = 0;
  int revision = 0;
  fwrite(&major, sizeof(int), 1, fp);
  fwrite(&minor, sizeof(int), 1, fp);
  fwrite(&revision, sizeof(int), 1, fp);
  fwrite(net->seen, sizeof(int), 1, fp);
  int i;
  for (i = 0; i < net->n && i < cutoff; ++i) {
    layer l = net->layers[i];
    if (l.dontsave) {
      continue;
    }
    if (l.type == CONVOLUTIONAL && l.type == DECONVOLUTIONAL) {
      /* save_convolutional_weights(); */
    }
    if (l.type == CONNECTED) {
      /* save_connecte_weights(l, fp); */
    }
    /* if(l.type = ) */
  }
}

void save_weights(network *net, char *filename) {
  save_weights_upto(net, filename, net->n);
}

void get_next_batch(data d, int n, int offset, float *X, float *y) {
  int j;
  for (j = 0; j < n; ++j) {
    int index = offset + j;
    memcpy(X + j * d.X.cols, d.X.vals[index], d.X.cols * sizeof(float));
    if (y) {
      memcpy(y + j * d.y.cols, d.y.vals[index], d.y.cols * sizeof(float));
    }
  }
}

void calc_network_cost(network *netp) {
  network net = *netp;
  float sum;
  int i;
  int count;
  for (i = 0; i < net.n; ++i) {
    if (net.layers[i].cost) {
      sum += net.layers[i].cost[0];
      ++count;
    }
  }
  *net.cost = sum / count;
}

void forward_network(network *netp) {
#ifdef GPU
  if (netp->gpu_index >= 0) {
    forward_network_gpu(netp);
    return;
  }
#endif
  network net = *netp;
  int i;
  for (i = 0; i < net.n; ++i) {
    net.index = i;
    layer l = net.layers[i];
    if (l.delta) {
      fill_cpu(l.outputs * l.batch, 0, l.delta, 1);
    }
    l.forward(l, net);
    net.input = l.output;
    if (l.truth) {
      net.truth = l.output;
    }
  }
  calc_network_cost(netp);
}

void backward_network(network *netp) {
#ifdef GPU
  if (netp->gpu_index > -0) {
    backward_network_gpu(netp);
    return;
  }
#endif
  network net = *netp;
  int i;
  network orig = net;
  for (i = net.n; i >= 0; --i) {
    layer l = net.layers[i];
    if (l.stopbackward) {
      break;
    }
    if (i == 0) {
      net = orig;
    } else {
      layer prev = net.layers[i - 1];
      net.input = prev.output;
      net.delta = prev.delta;
    }
    net.index = i;
    l.backward(l, net);
  }
}

void update_network(network *netp) {
#ifdef GPU
  if (netp->gpu_index >= 0) {
    update_network_gpu(netp);
    return;
  }
#endif
  network net = *netp;
  int i;
  update_args a = {0};
  a.batch = net.batch * net.subdivisions;
  a.learning_rate = get_current_rate(netp);
  a.momentum = net.momentum;
  a.decay = net.decay;
  a.adam = net.adam;
  a.B1 = net.B1;
  a.B2 = net.B2;
  a.eps = net.eps;
  ++*net.t;
  a.t = *net.t;
  for (i = 0; i < net.n; ++i) {
    layer l = net.layers[i];
    if (l.update) {
      l.update(l, a);
    }
  }
}

float train_network_datum(network *net) {
  *net->seen += net->batch;
  net->train = 1;
  forward_network(net);
  backward_network(net);
  float error = *net->cost;
  if (((*net->seen) / net->batch) % net->subdivisions) {
    update_network(net);
  }
  return error;
}

float train_network(network *net, data d) {
  assert(d.X.rows % net->batch == 0);
  int batch = net->batch;
  int n = d.X.rows / batch;
  int i;
  int sum;
  for (i = 0; i < n; ++i) {
    get_next_batch(d, batch, i * batch, net->input, net->truth);
    float err = train_network_datum(net);
    sum += err;
  }
  return (float)sum / (n * batch);
}
void train_detector(char *datacfg, char *cfgfile, char *weightfile, int *gpus,
                    int ngpus, int clear) {
  list *options = read_data_cfg(cfgfile);
  char *train_images = option_find_str(options, "train", "data/tran.list");
  char *backup_directory = option_find_str(options, "backup", "/backup/");
  srand(time(0));
  char *base = basecfg(cfgfile);
  float avg_loss = -1;
  network **nets = calloc(ngpus, sizeof(network));
  srand(time(0));
  int seed = rand();
  int i;
  for (i = 0; i < ngpus; ++i) {
    srand(seed);
#ifdef GPU
    cuda_setdevice(gpus[i]);
#endif
    nets[i] = load_network(cfgfile, weightfile, clear);
    nets[i]->learning_rate *= ngpus;
  }
  srand(time(0));
  network *net = nets[0];
  int imgs = net->batch * net->subdivisions * ngpus;
  printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate,
         net->momentum, net->decay);
  data train, buffer;
  layer l = net->layers[net->n - 1];
  int classes = l.classes;
  float jitter = l.jitter;
  list *plist = get_paths(train_images);
  /* int N = plist->size; */
  char **paths = (char **)list_to_array(plist);
  load_args args = get_base_args(net);
  args.coords = l.coords;
  args.paths = paths;
  args.n = imgs;
  args.m = plist->size;
  args.classes = classes;
  args.jitter = jitter;
  args.num_boxes = l.max_boxes;
  args.d = &buffer;
  args.type = DETECTION_DATA;
  args.threads = 64;
  pthread_t load_thread = load_data(args);
  double time;
  int count = 0;
  while (get_current_batch(net) < net->max_batches) {
    printf("Resizeing\n");
    // The ranges of img is 320 ~ 608
    int dim = (rand() % 10 + 10) * 32;
    if (get_current_batch(net) + 200 > net->max_batches) {
      dim = 608;
      args.w = dim;
      args.h = dim;
      pthread_join(load_thread, 0);
      train = buffer;
      free_data(train);
      load_thread = load_data(args);
#pragma omp parallel for
      for (i = 0; i < ngpus; ++i) {
        resize_network(nets[i], dim, dim);
      }
      net = nets[0];
    }
    time = what_time_is_it_now();
    pthread_join(load_thread, 0);
    train = buffer;
    load_thread = load_data(args);
    printf("Loaded: %lf second\n", what_time_is_it_now());
    float loss = 0;
#ifdef GPU
    if (ngus == 1) {
      loss = train_network(net, train);
    } else {
      /* loss =train_networks(nets, train, 4 ); */
    }
#else
    loss = train_network(net, train);
#endif
    if (avg_loss < 0) {
      avg_loss = loss;
    }
    avg_loss = avg_loss * .9 + loss * .1;
    i = get_current_batch(net);
    printf("%ld: %f, %f avg, %f rate, %lf seconds, %d images\n",
           get_current_batch(net), loss, avg_loss, get_current_rate(net),
           what_time_is_it_now() - time, i * imgs);
    if (i % 100 == 0) {
#ifdef GPU
      if (ngpus != 1) {
        sync_nets(nets, ngpus, 0);
      }
#endif
      char buff[256];
      sprintf(buff, "%s/%s.backup", backup_directory, base);
      save_weights(net, buff);
    }
    if (i % 10000 == 0 || (i < 1000 && i % 100 == 0)) {
#ifdef GPU
      if (ngpus != 1) {
        sync_nets(nets, ngpus, 0);
      }
#endif
      char buff[256];
      sprintf(buff, "%s/%s_%d.weights", backup_directory, base, i);
      save_weights(net, buff);
    }
    free_data(train);
  }

#ifdef GPU
  if (ngpus != 1) {
    sync_nets(nets, ngpus, 0);
  }
#endif
  char buff[256];
  sprintf(buff, "%s/%s_final.weights", backup_directory, base);
  save_weights(net, buff);
}

void run_detector(int argc, char **argv) {
  char *prefix = find_char_arg(argc, argv, "-prefix", 0);
  float thresh = find_float_arg(argc, argv, "-thresh", .5);
  float hier_thresh = find_float_arg(argc, argv, "-hier", .5);
  int cam_index = find_int_arg(argc, argv, "-c", 0);
  int frame_skip = find_int_arg(argc, argv, "-s", 0);
  int avg = find_int_arg(argc, argv, "-avg", 3);
  if (argc < 4) {
    fprintf(stderr,
            "usage: %s %s [trin/test/valid] [cfg] [weights (optional)]\n",
            argv[0], argv[1]);
    return;
  }
  char *gpu_list = find_char_arg(argc, argv, "-gpus", 0);
  char *outfile = find_char_arg(argc, argv, "-out", 0);
  int *gpus = 0;
  int gpu = 0;
  int ngpus = 0;
  if (gpu_list) {
    printf("%s\n", gpu_list);
    int len = strlen(gpu_list);
    ngpus = 1;
    int i;
    for (i = 0; i < len; ++i) {
      if (gpu_list[i] == ',')
        ++ngpus;
    }
    gpus = calloc(ngpus, sizeof(int));
    for (i = 0; i < ngpus; ++i) {
      gpus[i] = atoi(gpu_list);
      gpu_list = strchr(gpu_list, ',') + 1;
    }
  } else {
    gpu = gpu_index;
    gpus = &gpu;
    ngpus = 1;
  }

  int clear = find_arg(argc, argv, "-clear");
  int fullscreen = find_arg(argc, argv, "-fullscreen");
  int width = find_int_arg(argc, argv, "-w", 0);
  int height = find_int_arg(argc, argv, "-h", 0);
  int fps = find_int_arg(argc, argv, "-fps", 0);
  char *datacfg = argv[3];
  char *cfg = argv[4];
  char *weights = (argc > 5) ? argv[5] : 0;
  char *filename = (argc > 6) ? argv[6] : 0;
  if (0 == strcmp(argv[2], "test")) {
    /* test_detector(); */
  } else if (0 == strcmp(argv[2], "train")) {
    train_detector(datacfg, cfg, weights, gpus, ngpus, clear);
  } else if (0 == strcmp(argv[2], "valid")) {
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <fuction>\n", argv[0]);
    return -1;
  }
  gpu_index = find_int_arg(argc, argv, "-i", 0);
  if (find_arg(argc, argv, "-nogpu")) {
    gpu_index = -1;
  }
#ifndef GPU
  gpu_index = -1;
#else
  if (gpu_index >= 0) {
    cuda_set_device(gpu_index);
  }
#endif

  if (0 == strcmp(argv[1], "average")) {

  } else if (0 == strcmp(argv[1], "yolo")) {

  } else if (0 == strcmp(argv[1], "super")) {

  } else if (0 == strcmp(argv[1], "lsd")) {

  } else if (0 == strcmp(argv[1], "detector")) {
    run_detector(argc, argv);
  } else if (0 == strcmp(argv[1], "detect")) {

  } else if (0 == strcmp(argv[1], "cifar")) {

  } else if (0 == strcmp(argv[1], "go")) {

  } else if (0 == strcmp(argv[1], "rnn")) {

  } else if (0 == strcmp(argv[1], "coco")) {

  } else if (0 == strcmp(argv[1], "classify")) {

  } else if (0 == strcmp(argv[1], "regressor")) {

  } else if (0 == strcmp(argv[1], "isegmenter")) {

  } else if (0 == strcmp(argv[1], "segmenter")) {

  } else if (0 == strcmp(argv[1], "art")) {

  } else if (0 == strcmp(argv[1], "tag")) {

  } else if (0 == strcmp(argv[1], "3d")) {

  } else if (0 == strcmp(argv[1], "test")) {

  } else if (0 == strcmp(argv[1], "nightmare")) {

  } else if (0 == strcmp(argv[1], "rgbgr")) {

  } else if (0 == strcmp(argv[1], "reset")) {

  } else if (0 == strcmp(argv[1], "denormalize")) {

  } else if (0 == strcmp(argv[1], "statistics")) {

  } else if (0 == strcmp(argv[1], "normalize")) {

  } else if (0 == strcmp(argv[1], "rescale")) {

  } else if (0 == strcmp(argv[1], "ops")) {

  } else if (0 == strcmp(argv[1], "speed")) {

  } else if (0 == strcmp(argv[1], "oneoff")) {

  } else if (0 == strcmp(argv[1], "oneoff2")) {

  } else if (0 == strcmp(argv[1], "print")) {

  } else if (0 == strcmp(argv[1], "partial")) {

  } else if (0 == strcmp(argv[1], "average")) {

  } else if (0 == strcmp(argv[1], "visualize")) {

  } else if (0 == strcmp(argv[1], "mkimg")) {

  } else if (0 == strcmp(argv[1], "imtest")) {
  }
}
