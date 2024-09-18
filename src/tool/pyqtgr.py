import pyqtgraph as pg
from PyQt5.QtCore import Qt
from PyQt5 import QtWidgets

attack = dict()
attack["start"] = 0
attack["end"] = 1
attack["bend"] = 1
attack["len"] = 200
attack["x_val"] = attack["len"]

decay = dict()
decay["start"] = attack["end"]
decay["end"] = attack["end"] - 0.3
decay["bend"] = 0.6
decay["len"] = 80
decay["x_val"] = attack["x_val"] + decay["len"]

sustain = dict()
sustain["start"] = decay["end"]
sustain["end"] = decay["end"]
sustain["bend"] = 0.3
sustain["len"] = 220
sustain["x_val"] = attack["x_val"] + decay["x_val"] + sustain["len"]

release = dict()
release["start"] = sustain["end"]
release["end"] = 0
release["bend"] = 0.5
release["len"] = 400
release["x_val"] = attack["x_val"] + decay["x_val"] + sustain["x_val"]

def linCurve(section: dict) -> list:
    vals = list()
    for i in range(section["len"]):
        pos = i/section["len"]
        vals.append((section["end"] - section["start"]) * pos + section["start"])
    return vals

def expCurve (section: dict) -> list:
    vals = list()
    for i in range(section["len"]):
        pos = i/section["len"]
        vals.append((section["end"] - section["start"]) * pow(pos, section["bend"]) + section["start"])
    return vals

def calc_plot():
    adsr_curve = expCurve(attack) + expCurve(decay) + expCurve(sustain) + expCurve(release)
    return adsr_curve


def findNearestSection(xdata, ydata) -> tuple[dict, dict]:
    if approx (xdata,ydata, attack["len"], attack["end"]):
        return (attack, decay)

    if approx (xdata,ydata, attack["len"] + decay["len"], decay["end"]):
        return (decay, sustain)

    if approx (xdata,ydata, attack["len"] + decay["len"] + sustain["len"], sustain["end"]):
        return (sustain, release)
    else: return  (dict(), dict())


def findNearestPointXY(xdata, ydata) -> tuple[float, float]:
    if approx (xdata,ydata, attack["len"], attack["end"]):
        return (attack["len"], attack["end"])

    if approx (xdata,ydata, attack["len"] + decay["len"], decay["end"]):
        return (attack["len"] + decay["len"], decay["end"])

    if approx (xdata,ydata, attack["len"] + decay["len"] + sustain["len"], sustain["end"]):
        return (attack["len"] + decay["len"] + sustain["len"], sustain["end"])
    else: return  (-1, -1)

def approx (x, y, tar_x, tar_y, abs_x=20, abs_y=0.02) -> bool:
    match_x = False
    match_y = False
    if x <= tar_x and x + abs_x >= tar_x: 
        match_x = True
    if x >= tar_x and x - abs_x <= tar_x: 
        match_x = True
    if y <= tar_y and y + abs_y >= tar_y: 
        match_y = True
    if y >= tar_y and y - abs_y <= tar_y: 
        match_y = True
    if match_x == True and match_y == True:
        return True
    else:
        return False

def clip_1_0(val: float):
    if val >= 1.0:
        return 1.0
    elif val <= 0.0:
        return 0.0
    else:
        return val
    

class ADSRPlot(pg.PlotWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.adsr_plot = None
        self.point_plot = None
        self.mouse_down = False
        self.active_end = dict()
        self.active_start = dict()
        self.active_y = None
        self.setYRange(0, 1)

    def coords(self, ev) -> tuple[int, float]:
        vb = self.getViewBox()
        data_pos = vb.mapSceneToView(ev.pos())
        x, y = int(data_pos.x()), clip_1_0(data_pos.y())

        return (x, y)

    def draw_point(self, x, y):
        if self.point_plot is not None:
            self.point_plot.setData([x], [y])
        else:
             self.point_plot = self.plot([x], [y], pen=None, marker='o', symbolBrush='r')
    def check_remove(self):
        if self.point_plot in self.items():
            self.removeItem(self.point_plot)
            self.point_plot = None

    def mousePressEvent(self, ev):
        self.mouse_down = True
        x, y = self.coords(ev)
        x_near, y_near = findNearestPointXY(x, y)
        if x_near < 0 or y_near < 0:
            return 
        QtWidgets.QApplication.setOverrideCursor(Qt.CursorShape.SizeVerCursor)
        end, start = findNearestSection(x, y)
        self.active_end = end
        self.active_start = start
        super().mousePressEvent(ev)
        
    def mouseReleaseEvent(self, ev):
        x, y = self.coords(ev)
        if self.mouse_down:
            QtWidgets.QApplication.restoreOverrideCursor()
            self.active_end["end"] = y
            # self.active_end["x_val"] = x # TODO: clean x position after drag
            self.active_start["start"] = y
            self.update_plot(calc_plot())
        self.mouse_down = False
        super().mouseReleaseEvent(ev)
        
    def mouseMoveEvent(self, ev):
        x, y = self.coords(ev)
        x_near, y_near = findNearestPointXY(x, y)
        if x_near < 0 or y_near < 0:
            self.check_remove()
            return
        self.draw_point(x_near,y_near)
        super().mouseMoveEvent(ev)
    
    def update_plot_xy(self, x, y):
        if self.adsr_plot is not None:
            self.adsr_plot.setData(x, y)
        else:
            self.plot_graph.adsr_plot = self.plot_graph.plot(y)

    def update_plot(self, data):
        if self.adsr_plot is not None:
            self.adsr_plot.setData(list(range(len(data))), data)
        else:
            self.adsr_plot = self.plot(data, pen=pg.mkPen({'color': '#E5C07B', 'width': 2}))

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()

        # Temperature vs time plot
        self.plot_graph = ADSRPlot()
        self.setCentralWidget(self.plot_graph)
        self.plot_graph.getViewBox().setMouseEnabled(x=False, y=False)
        self.plot_graph.setBackground('#282C34')
        self.plot_graph.update_plot(calc_plot())

app = QtWidgets.QApplication([])
main = MainWindow()
main.show()
app.exec()
