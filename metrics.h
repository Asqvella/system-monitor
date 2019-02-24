// Working with metric
typedef struct {
	int time;
	int traffic;
	int ram;
	int hdd;
	int cpu;
	int cpu_temp;
	int hdd_temp;
	int mb_temp;
} points;
void get_points(points *p);
void add_points_to_db(points *p);
void check_and_alert(points *p);
