% --- Создается пустая цель ПОИ
function makeEmptyPOI()
    POI.x = [];
    POI.y = [];
    POI.z = [];
    POI.Vr = [];
    POI.t = [];
    assignin('base','POI',POI);