% --- Создается пустая цель ВОИ
function makeEmptyVOI()
    VOI.x = [];
    VOI.y = [];
    VOI.z = [];
    VOI.Vx = [];
    VOI.Vy = [];
    VOI.Vz = [];
    VOI.ax = [];
    VOI.ay = [];
    VOI.az = [];
    VOI.t = [];
    assignin('base','VOI',VOI);