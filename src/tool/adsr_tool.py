import wx
import wx.lib.mixins.inspection as WIT

import numpy as np

from matplotlib.backends.backend_wxagg import FigureCanvasWxAgg as FigureCanvas
from matplotlib.backends.backend_wxagg import \
    NavigationToolbar2WxAgg as NavigationToolbar

from matplotlib.figure import Figure


attack = dict()
attack["start"] = 0
attack["end"] = 1
attack["bend"] = 1
attack["len"] = 200

decay = dict()
decay["start"] = attack["end"]
decay["end"] = attack["end"] - 0.3
decay["bend"] = 0.6
decay["len"] = 80

sustain = dict()
sustain["start"] = decay["end"]
sustain["end"] = decay["end"]
sustain["bend"] = 0.3
sustain["len"] = 220

release = dict()
release["start"] = sustain["end"]
release["end"] = 0
release["bend"] = 0.5
release["len"] = 400


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

class CanvasFrame(wx.Frame):
    def __init__(self):
        super().__init__(None, -1, 'CanvasFrame', size=(800, 500))
        self.figure = Figure()
        self.axes = self.figure.add_subplot()
        self.axes.set_facecolor("lightsteelblue")

        self.line, = self.axes.plot(calc_plot(), color="yellow")
        self.canvas = FigureCanvas(self, -1, self.figure)
        self.canvas.mpl_connect('button_release_event', self.on_release)
        self.canvas.mpl_connect('button_press_event', self.on_click)
        self.canvas.mpl_connect('motion_notify_event', self.mouse_move)
        

        self.vert_sizer = wx.BoxSizer(wx.VERTICAL)
        self.vert_sizer.Add(self.canvas, 1, wx.LEFT | wx.TOP | wx.EXPAND)
        self.SetSizer(self.vert_sizer)
        self.Fit()

    def on_release(self, event):
        section, next_section = self.findNearestPoint(event.xdata)
        section["len"] = int(event.xdata)
        section["end"] = event.ydata
        next_section["start"] = event.ydata
        self.axes.clear()
        self.axes.plot(calc_plot())
        self.canvas.draw()

    def on_click(self, event):
        section, next_section = self.findNearestPoint(event.xdata)
        section["len"] = int(event.xdata)
        section["end"] = event.ydata
        next_section["start"] = event.ydata
        self.axes.clear()
        self.axes.plot(calc_plot())
        self.canvas.draw()

    def mouse_move(self, event):
        if not type(event.xdata) == np.float64: return
        if not type(event.ydata) == np.float64: return
        xpos, ypos = self.findNearestPointXY(event.xdata, event.ydata)
        if xpos < 0 or ypos < 0:
            return
        self.axes.clear()
        self.axes.plot(xpos,ypos, marker="o", markersize=5)
        self.axes.plot(calc_plot(), color="yellow")
        self.canvas.draw()

    def AdjAttackTime(self, event):
        obj = event.GetEventObject()
        val = obj.GetValue()
        attack["len"] = val
        self.axes.clear()
        self.axes.plot(calc_plot(), color="yellow")
        self.canvas.draw()

    def AdjDecayTime(self, event):
        obj = event.GetEventObject()
        val = obj.GetValue()
        decay["len"] = val
        self.axes.clear()
        self.axes.plot(calc_plot(), color="yellow")
        self.canvas.draw()

    def AdjSustainAmp(self, event):
        obj = event.GetEventObject()
        val = obj.GetValue()
        sustain["end"] = val / 100
        release["start"] = val / 100
        self.axes.clear()
        self.axes.plot(calc_plot(), color="yellow")
        self.canvas.draw()

    def findNearestPoint(self, xdata) -> tuple[dict, dict]:
        if xdata < attack["len"]: return (attack,decay)
        if xdata < (attack["len"] + decay["len"]): return (decay, sustain)
        if xdata < (attack["len"] + decay["len"] + sustain["end"]): return (sustain, release)
        else: return (sustain, release)

    def findNearestPointXY(self, xdata, ydata) -> tuple[float, float]:
        if approx (xdata,ydata, attack["len"], attack["end"]):
            return (attack["len"], attack["end"])

        if approx (xdata,ydata, attack["len"] + decay["len"], decay["end"]):
            return (attack["len"] + decay["len"], decay["end"])

        if approx (xdata,ydata, attack["len"] + decay["len"] + sustain["len"], sustain["end"]):
            return (attack["len"] + decay["len"] + sustain["len"], sustain["end"])
        else: return  (-1, -1)


def approx (x, y, tar_x, tar_y) -> bool:
    abs_y = 0.1
    abs_x = 10
    match_x = False
    match_y = False
    if x < tar_x and x + abs_x > tar_x: 
        match_x = True
    if y < tar_y and y + abs_y > tar_y: 
        match_y = True
    if match_x == True and match_y == True:
        return True
    else:
        return False
    

# Alternatively you could use:
# class App(wx.App):
class App(WIT.InspectableApp):
    def OnInit(self):
        """Create the main window and insert the custom frame."""
        self.Init()
        frame = CanvasFrame()
        frame.Show(True)

        return True


if __name__ == "__main__":
    app = App()
    app.MainLoop()
