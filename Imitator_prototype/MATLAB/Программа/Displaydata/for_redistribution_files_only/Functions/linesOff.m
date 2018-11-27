% --- Убираются все линии с графика
function linesOff()
    realPlot = evalin('base','realPlot');
    realIndex = evalin('base','realIndex');
    voiPlot = evalin('base','voiPlot');
    voiIndex = evalin('base','voiIndex');
    
    setLinesOff(realPlot(realIndex));
    setLinesOff(voiPlot(voiIndex));