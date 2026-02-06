
#ifndef _SML_SCRIPTS_H_
#define _SML_SCRIPTS_H_

// URLs für Remote-Scripts
#define SCRIPT_SML_DOWNLOAD_URL "https://raw.githubusercontent.com/waldy83/Tasmota-Scripts/master/gas/"
#define SCRIPT_SML_DOWNLOAD_URL_SMARTMETERS "https://raw.githubusercontent.com/waldy83/Tasmota-Scripts/master/gas/index.json"

// --- SCRIPT 1: Gaszähler Einfach ---
#define SCRIPT_GAS_SIMPLE "" \
    ">D\\n" \
    ">B\\n" \
    "->sensor53 r\\n" \
    "->sensor53 c1 0\\n" \
    ">M 1\\n" \
    "+1,14,c,1,-500,Gas\\n" \
    "1,1-0:1.8.0*255(@100,Gesamtverbrauch,m3,total,2)\\n" \
    "#\\n"

// --- SCRIPT 2: Gaszähler mit Tages/Monats/Jahres-Verbrauch
#define SCRIPT_GAS_HISTORY "" \
    ">D\\n" \
    ">B\\n" \
    "->sensor53 r\\n" \
    "->sensor53 c1 0\\n" \
    ">M 1\\n" \
    "+1,14,c,1,-500,Gas\\n" \
    "1,1-0:1.8.0*255(@100,Gesamtverbrauch,m3,total,2)\\n" \
    "#\\n"

// --- HTML Auswahl-Menü ---
#define SCRIPT_SML_SELECT_OPTIONS "" \
    "<option value='sm_0'>--- Scriptauswahl ---</option>" \
    "<option value='gas_1'>Standard</option>" \
    "<option value='gas_2'>Historie</option>"

#define SCRIPT_SML_SELECT_FUNCTION "" \
    "if(selSM.value=='sm_0'){ta.innerHTML=''}" \
    "else if(selSM.value=='gas_1'){ta.innerHTML='" SCRIPT_GAS_SIMPLE "'}" \
    "else if(selSM.value=='gas_2'){ta.innerHTML='" SCRIPT_GAS_HISTORY "'}" \
    "else{ta.innerHTML='';fetch('" SCRIPT_SML_DOWNLOAD_URL "'+selSM.value,{cache:'no-store'}).then(response=>response.text()).then(content=>{ta.innerHTML=content;});}"

#define SCRIPT_SML_SELECT "" \
    "<p><select id='idSelSM'>" SCRIPT_SML_SELECT_OPTIONS "</select></p>"

// --- JavaScript Handler ---
#define SCRIPT_SML_SELECT_HANDLER "" \
    "var selSM=eb('idSelSM');" \
    "selSM.onchange=function(){" SCRIPT_SML_SELECT_FUNCTION "};" \
    "fetch('" SCRIPT_SML_DOWNLOAD_URL_SMARTMETERS "',{cache:'no-store'}).then(response=>response.json()).then(data=>{" \
    "if(data && data.smartmeters && data.smartmeters.length){" \
    "while(selSM.options.length>1){selSM.options.remove(1);}" \
    "for(let n=0;n<data.smartmeters.length;n++){" \
    "let o=document.createElement('option');o.value=data.smartmeters[n].filename;o.text=data.smartmeters[n].label;selSM.options.add(o);" \
    "}}});"

#endif
