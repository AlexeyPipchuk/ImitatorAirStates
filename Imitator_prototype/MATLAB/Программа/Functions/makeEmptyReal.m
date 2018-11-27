% --- Создается пустая цель эталона
function makeEmptyReal()
    Real.x = [];
    Real.y = [];
    Real.z = [];
    Real.Vx = [];
    Real.Vy = [];
    Real.Vz = [];
    Real.ax = [];
    Real.ay = [];
    Real.az = [];
    Real.t = [];
    assignin('base','Real',Real);