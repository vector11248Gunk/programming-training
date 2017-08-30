#include "widget.h"
#include "ui_widget.h"
#include "sudoku_grid.h"
#include "config.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	int fixed_size = FIXED_SIZE;
	int cell_size = CELL_SIZE;
	int cell_span = cell_size * cell_size;

	layout = new QVBoxLayout(this);
	top_layout = new QHBoxLayout;
	bottom_layout = new QHBoxLayout;

	layout->addLayout(top_layout);
	layout->addLayout(bottom_layout);

	grid = new SudokuGrid(cell_size, fixed_size);
	bottom_layout->addWidget(grid);

	// init digit button layout
	QLabel *digit_layout_wrap = new QLabel;
	int size = (fixed_size + 1) * cell_span + GRID_SPACING + 1;
	digit_layout_wrap->setFixedSize(fixed_size + GRID_SPACING * 2, size);
	digit_layout_wrap->setStyleSheet(
		"QLabel { background-color: " GRID_BG_COLOR ";}"
		"QPushButton{ "
				"border:none;"
				"background-color: " DEFAULT_BG_COLOR "; }"
		"QPushButton:pressed {"
				"border:none;"
				"background-color: " PRESSED_BG_COLOR "; }"
		"QPushButton:hover:!pressed {"
				"border:none;"
				"background-color: " HOVER_BG_COLOR "; }"
	);

	digit_button_layout = new QGridLayout(digit_layout_wrap);
	digit_button_layout->setMargin(GRID_SPACING);
	digit_button_layout->setSpacing(CELL_SPACING);

	bottom_layout->addWidget(digit_layout_wrap);

	QSignalMapper *m = new QSignalMapper(this);
	for(int i = 1; i <= cell_span; ++i)
	{
		QPushButton *btn = new QPushButton(QString::number(i));

		btn->setFixedSize(fixed_size, fixed_size);

		m->setMapping(btn, i);
		connect(btn, SIGNAL(clicked()), m, SLOT(map()));

		digit_button_layout->addWidget(btn, i - 1, 0);
		digit_btns.push_back(btn);
	}

	connect(m, SIGNAL(mapped(int)), grid, SLOT(add_value(int)));

	timer = new Timer;

	start_btn = new QPushButton("Start");
	connect(start_btn, SIGNAL(clicked()), grid, SLOT(game_start()));
	connect(start_btn, SIGNAL(clicked()), timer, SLOT(restart_timer()));

	pause_btn = new QPushButton("Pause");
	connect(pause_btn, SIGNAL(clicked()), timer, SLOT(toggle_timer()));
	connect(pause_btn, SIGNAL(clicked()), this, SLOT(toggle_button()));

	hint_btn = new QPushButton("Hint");
	connect(hint_btn, SIGNAL(clicked()), grid, SLOT(game_hint()));

	clear_btn = new QPushButton("Clear");
	connect(clear_btn, SIGNAL(clicked()), grid, SLOT(clear_grid()));

	backward_btn = new QPushButton("Backward");
	connect(backward_btn, SIGNAL(clicked()), grid, SLOT(backward_step()));

	forward_btn = new QPushButton("Forward");
	connect(forward_btn, SIGNAL(clicked()), grid, SLOT(forward_step()));

	top_layout->addWidget(start_btn);
	top_layout->addWidget(pause_btn);
	top_layout->addWidget(hint_btn);
	top_layout->addWidget(clear_btn);
	top_layout->addWidget(backward_btn);
	top_layout->addWidget(forward_btn);
	top_layout->addWidget(timer);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::toggle_button()
{
}
