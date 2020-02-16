/*
 * iodef.h
 *
 *  Created on: 18 ���. 2018 �.
 *      Author: Roman
 */

#ifndef IODEF_H_
#define IODEF_H_

#define TMRms1 tmrms[0]
#define TMRms2 tmrms[1]
#define TMRms3 tmrms[2]
#define TMRms4 tmrms[3]
#define TMRs8 tmrs[7]
#define TMRs1 tmrs[0]
#define TMRs2 tmrs[1]
#define TMRs3 tmrs[2]
#define TMRs4 tmrs[3]
#define AI1 ain[0]
#define AI2 ain[1]
#define AI3 ain[2]
#define AI4 ain[3]
#define AI5 ain[4]
#define AI6 ain[5]
#define AI7 ain[6]
#define AI8 ain[7]
#define AI9 ain[8]
#define AI10 ain[9]
#define AI11 ain[10]
#define AI12 ain[11]
#define AI13 ain[12]
#define AI14 ain[13]
#define AI1_RAW ain_raw[0]
#define AI2_RAW ain_raw[1]
#define AI3_RAW ain_raw[2]
#define AI4_RAW ain_raw[3]
#define AI5_RAW ain_raw[4]
#define AI6_RAW ain_raw[5]
#define AI7_RAW ain_raw[6]
#define AI8_RAW ain_raw[7]
#define AI9_RAW ain_raw[8]
#define AI10_RAW ain_raw[9]
#define AI11_RAW ain_raw[10]
#define AI12_RAW ain_raw[11]
#define AI13_RAW ain_raw[12]
#define AI14_RAW ain_raw[13]
#define AI1_UNDER ain_under[0]
#define AI2_UNDER ain_under[1]
#define AI3_UNDER ain_under[2]
#define AI4_UNDER ain_under[3]
#define AI5_UNDER ain_under[4]
#define AI6_UNDER ain_under[5]
#define AI7_UNDER ain_under[6]
#define AI8_UNDER ain_under[7]
#define AI9_UNDER ain_under[8]
#define AI10_UNDER ain_under[9]
#define AI11_UNDER ain_under[10]
#define AI12_UNDER ain_under[11]
#define AI13_UNDER ain_under[12]
#define AI14_UNDER ain_under[13]
#define AI1_OVER ain_over[0]
#define AI2_OVER ain_over[1]
#define AI3_OVER ain_over[2]
#define AI4_OVER ain_over[3]
#define AI5_OVER ain_over[4]
#define AI6_OVER ain_over[5]
#define AI7_OVER ain_over[6]
#define AI8_OVER ain_over[7]
#define AI9_OVER ain_over[8]
#define AI10_OVER ain_over[9]
#define AI11_OVER ain_over[10]
#define AI12_OVER ain_over[11]
#define AI13_OVER ain_over[12]
#define AI14_OVER ain_over[13]
#define AI1_ALARM ain_alarm[0]
#define AI2_ALARM ain_alarm[1]
#define AI3_ALARM ain_alarm[2]
#define AI4_ALARM ain_alarm[3]
#define AI5_ALARM ain_alarm[4]
#define AI6_ALARM ain_alarm[5]
#define AI7_ALARM ain_alarm[6]
#define AI8_ALARM ain_alarm[7]
#define AI9_ALARM ain_alarm[8]
#define AI10_ALARM ain_alarm[9]
#define AI11_ALARM ain_alarm[10]
#define AI12_ALARM ain_alarm[11]
#define AI13_ALARM ain_alarm[12]
#define AI14_ALARM ain_alarm[13]
#define DI1 din[0]
#define DI2 din[1]
#define DI3 din[2]
#define DI4 din[3]
#define DI5 din[4]
#define DI6 din[5]
#define DI7 din[6]
#define DI8 din[7]
#define DI9 din[8]
#define DI10 din[9]
#define DI11 din[10]
#define DI12 din[11]
#define DI13 din[12]
#define DI14 din[13]
#define DI1_FAULT	din_fault[0]
#define DI2_FAULT	din_fault[1]
#define DI3_FAULT	din_fault[2]
#define DI4_FAULT	din_fault[3]
#define DI5_FAULT	din_fault[4]
#define DI6_FAULT	din_fault[5]
#define DI7_FAULT	din_fault[6]
#define DI8_FAULT	din_fault[7]
#define DI9_FAULT	din_fault[8]
#define DI10_FAULT	din_fault[9]
#define DI11_FAULT	din_fault[10]
#define DI12_FAULT	din_fault[11]
#define DI13_FAULT	din_fault[12]
#define DI14_FAULT	din_fault[13]
#define DI1_BREAK	din_break[0]
#define DI2_BREAK	din_break[1]
#define DI3_BREAK	din_break[2]
#define DI4_BREAK	din_break[3]
#define DI5_BREAK	din_break[4]
#define DI6_BREAK	din_break[5]
#define DI7_BREAK	din_break[6]
#define DI8_BREAK	din_break[7]
#define DI9_BREAK	din_break[8]
#define DI10_BREAK	din_break[9]
#define DI11_BREAK	din_break[10]
#define DI12_BREAK	din_break[11]
#define DI13_BREAK	din_break[12]
#define DI14_BREAK	din_break[13]
#define DI1_SHORT	din_short_circuit[0]
#define DI2_SHORT	din_short_circuit[1]
#define DI3_SHORT	din_short_circuit[2]
#define DI4_SHORT	din_short_circuit[3]
#define DI5_SHORT	din_short_circuit[4]
#define DI6_SHORT	din_short_circuit[5]
#define DI7_SHORT	din_short_circuit[6]
#define DI8_SHORT	din_short_circuit[7]
#define DI9_SHORT	din_short_circuit[8]
#define DI10_SHORT	din_short_circuit[9]
#define DI11_SHORT	din_short_circuit[10]
#define DI12_SHORT	din_short_circuit[11]
#define DI13_SHORT	din_short_circuit[12]
#define DI14_SHORT	din_short_circuit[13]
#define DO1 dout[0]
#define DO2 dout[1]
#define DO3 dout[2]
#define DO4 dout[3]
#define DO5 dout[4]
#define DO6 dout[5]
#define IB1 ibit[0]
#define IB2 ibit[1]
#define IB3 ibit[2]
#define IB4 ibit[3]
#define IB5 ibit[4]
#define IB6 ibit[5]
#define IB7 ibit[6]
#define IB8 ibit[7]
#define IB9 ibit[8]
#define IB10 ibit[9]
#define IB11 ibit[10]
#define IB12 ibit[11]
#define IB13 ibit[12]
#define IB14 ibit[13]
#define IB15 ibit[14]
#define IB16 ibit[15]
#define IB17 ibit[16]
#define IB18 ibit[17]
#define IB19 ibit[18]
#define IB20 ibit[19]
#define IB21 ibit[20]
#define IB22 ibit[21]
#define IB23 ibit[22]
#define IB24 ibit[23]
#define IB25 ibit[24]
#define IB26 ibit[25]
#define IB27 ibit[26]
#define IB28 ibit[27]
#define IB29 ibit[28]
#define IB30 ibit[29]
#define IB31 ibit[30]
#define IB32 ibit[31]
#define IB33 ibit[32]
#define IB34 ibit[33]
#define IB35 ibit[34]
#define IB36 ibit[35]
#define IB37 ibit[36]
#define IB38 ibit[37]
#define IB39 ibit[38]
#define IB40 ibit[39]
#define IB41 ibit[40]
#define IB42 ibit[41]
#define IB43 ibit[42]
#define IB44 ibit[43]
#define IB45 ibit[44]
#define IB46 ibit[45]
#define IB47 ibit[46]
#define IB48 ibit[47]
#define IB49 ibit[48]
#define IB50 ibit[49]
#define IB51 ibit[50]
#define IB52 ibit[51]
#define IB53 ibit[52]
#define IB54 ibit[53]
#define IB55 ibit[54]
#define IB56 ibit[55]
#define IB57 ibit[56]
#define IB58 ibit[57]
#define IB59 ibit[58]
#define IB60 ibit[59]
#define IB61 ibit[60]
#define IB62 ibit[61]
#define IB63 ibit[62]
#define IB64 ibit[63]
#define IB65 ibit[64]
#define IB66 ibit[65]
#define IB67 ibit[66]
#define IB68 ibit[67]
#define IB69 ibit[68]
#define IB70 ibit[69]
#define IB71 ibit[70]
#define IB72 ibit[71]
#define IB73 ibit[72]
#define IB74 ibit[73]
#define IB75 ibit[74]
#define IB76 ibit[75]
#define IB77 ibit[76]
#define IB78 ibit[77]
#define IB79 ibit[78]
#define IB80 ibit[79]
#define IB81 ibit[80]
#define IB82 ibit[81]
#define IB83 ibit[82]
#define IB84 ibit[83]
#define IB85 ibit[84]
#define IB86 ibit[85]
#define IB87 ibit[86]
#define IB88 ibit[87]
#define IB89 ibit[88]
#define IB90 ibit[89]
#define IB91 ibit[90]
#define IB92 ibit[91]
#define IB93 ibit[92]
#define IB94 ibit[93]
#define IB95 ibit[94]
#define IB96 ibit[95]
#define IB97 ibit[96]
#define IB98 ibit[97]
#define IB99 ibit[98]
#define IB100 ibit[99]
#define IB101 ibit[100]
#define IB102 ibit[101]
#define IB103 ibit[102]
#define IB104 ibit[103]
#define IB105 ibit[104]
#define IB106 ibit[105]
#define IB107 ibit[106]
#define IB108 ibit[107]
#define IB109 ibit[108]
#define IB110 ibit[109]
#define IB111 ibit[110]
#define IB112 ibit[111]
#define IB113 ibit[112]
#define IB114 ibit[113]
#define IB115 ibit[114]
#define IB116 ibit[115]
#define IB117 ibit[116]
#define IB118 ibit[117]
#define IB119 ibit[118]
#define IB120 ibit[119]
#define IB121 ibit[120]
#define IB122 ibit[121]
#define IB123 ibit[122]
#define IB124 ibit[123]
#define IB125 ibit[124]
#define IB126 ibit[125]
#define IB127 ibit[126]
#define IB128 ibit[127]
#define IB129 ibit[128]
#define IB130 ibit[129]
#define IB131 ibit[130]
#define IB132 ibit[131]
#define IB133 ibit[132]
#define IB134 ibit[133]
#define IB135 ibit[134]
#define IB136 ibit[135]
#define IB137 ibit[136]
#define IB138 ibit[137]
#define IB139 ibit[138]
#define IB140 ibit[139]
#define IB141 ibit[140]
#define IB142 ibit[141]
#define IB143 ibit[142]
#define IB144 ibit[143]
#define IB145 ibit[144]
#define IB146 ibit[145]
#define IB147 ibit[146]
#define IB148 ibit[147]
#define IB149 ibit[148]
#define IB150 ibit[149]
#define IB151 ibit[150]
#define IB152 ibit[151]
#define IB153 ibit[152]
#define IB154 ibit[153]
#define IB155 ibit[154]
#define IB156 ibit[155]
#define IB157 ibit[156]
#define IB158 ibit[157]
#define IB159 ibit[158]
#define IB160 ibit[159]
#define IB161 ibit[160]
#define IB162 ibit[161]
#define IB163 ibit[162]
#define IB164 ibit[163]
#define IB165 ibit[164]
#define IB166 ibit[165]
#define IB167 ibit[166]
#define IB168 ibit[167]
#define IB169 ibit[168]
#define IB170 ibit[169]
#define IB171 ibit[170]
#define IB172 ibit[171]
#define IB173 ibit[172]
#define IB174 ibit[173]
#define IB175 ibit[174]
#define IB176 ibit[175]
#define IB177 ibit[176]
#define IB178 ibit[177]
#define IB179 ibit[178]
#define IB180 ibit[179]
#define IB181 ibit[180]
#define IB182 ibit[181]
#define IB183 ibit[182]
#define IB184 ibit[183]
#define IB185 ibit[184]
#define IB186 ibit[185]
#define IB187 ibit[186]
#define IB188 ibit[187]
#define IB189 ibit[188]
#define IB190 ibit[189]
#define IB191 ibit[190]
#define IB192 ibit[191]
#define IB193 ibit[192]
#define IB194 ibit[193]
#define IB195 ibit[194]
#define IB196 ibit[195]
#define IB197 ibit[196]
#define IB198 ibit[197]
#define IB199 ibit[198]
#define IB200 ibit[199]
#define IB201 ibit[200]
#define IB202 ibit[201]
#define IB203 ibit[202]
#define IB204 ibit[203]
#define IB205 ibit[204]
#define IB206 ibit[205]
#define IB207 ibit[206]
#define IB208 ibit[207]
#define IB209 ibit[208]
#define IB210 ibit[209]
#define IB211 ibit[210]
#define IB212 ibit[211]
#define IB213 ibit[212]
#define IB214 ibit[213]
#define IB215 ibit[214]
#define IB216 ibit[215]
#define IB217 ibit[216]
#define IB218 ibit[217]
#define IB219 ibit[218]
#define IB220 ibit[219]
#define IB221 ibit[220]
#define IB222 ibit[221]
#define IB223 ibit[222]
#define IB224 ibit[223]
#define IB225 ibit[224]
#define IB226 ibit[225]
#define IB227 ibit[226]
#define IB228 ibit[227]
#define IB229 ibit[228]
#define IB230 ibit[229]
#define IB231 ibit[230]
#define IB232 ibit[231]
#define IB233 ibit[232]
#define IB234 ibit[233]
#define IB235 ibit[234]
#define IB236 ibit[235]
#define IB237 ibit[236]
#define IB238 ibit[237]
#define IB239 ibit[238]
#define IB240 ibit[239]
#define IB241 ibit[240]
#define IB242 ibit[241]
#define IB243 ibit[242]
#define IB244 ibit[243]
#define IB245 ibit[244]
#define IB246 ibit[245]
#define IB247 ibit[246]
#define IB248 ibit[247]
#define IB249 ibit[248]
#define IB250 ibit[249]
#define IB251 ibit[250]
#define IB252 ibit[251]
#define IB253 ibit[252]
#define IB254 ibit[253]
#define IB255 ibit[254]
#define IB256 ibit[255]
#define IB257 ibit[256]
#define IB258 ibit[257]
#define IB259 ibit[258]
#define IB260 ibit[259]
#define IB261 ibit[260]
#define IB262 ibit[261]
#define IB263 ibit[262]
#define IB264 ibit[263]
#define IB265 ibit[264]
#define IB266 ibit[265]
#define IB267 ibit[266]
#define IB268 ibit[267]
#define IB269 ibit[268]
#define IB270 ibit[269]
#define IB271 ibit[270]
#define IB272 ibit[271]
#define IB273 ibit[272]
#define IB274 ibit[273]
#define IB275 ibit[274]
#define IB276 ibit[275]
#define IB277 ibit[276]
#define IB278 ibit[277]
#define IB279 ibit[278]
#define IB280 ibit[279]
#define IB281 ibit[280]
#define IB282 ibit[281]
#define IB283 ibit[282]
#define IB284 ibit[283]
#define IB285 ibit[284]
#define IB286 ibit[285]
#define IB287 ibit[286]
#define IB288 ibit[287]
#define IB289 ibit[288]
#define IB290 ibit[289]
#define IB291 ibit[290]
#define IB292 ibit[291]
#define IB293 ibit[292]
#define IB294 ibit[293]
#define IB295 ibit[294]
#define IB296 ibit[295]
#define IB297 ibit[296]
#define IB298 ibit[297]
#define IB299 ibit[298]
#define IB300 ibit[299]
#define IB301 ibit[300]
#define IB302 ibit[301]
#define IB303 ibit[302]
#define IB304 ibit[303]
#define IB305 ibit[304]
#define IB306 ibit[305]
#define IB307 ibit[306]
#define IB308 ibit[307]
#define IB309 ibit[308]
#define IB310 ibit[309]
#define IB311 ibit[310]
#define IB312 ibit[311]
#define IB313 ibit[312]
#define IB314 ibit[313]
#define IB315 ibit[314]
#define IB316 ibit[315]
#define IB317 ibit[316]
#define IB318 ibit[317]
#define IB319 ibit[318]
#define IB320 ibit[319]
#define IB321 ibit[320]
#define IB322 ibit[321]
#define IB323 ibit[322]
#define IB324 ibit[323]
#define IB325 ibit[324]
#define IB326 ibit[325]
#define IB327 ibit[326]
#define IB328 ibit[327]
#define IB329 ibit[328]
#define IB330 ibit[329]
#define IB331 ibit[330]
#define IB332 ibit[331]
#define IB333 ibit[332]
#define IB334 ibit[333]
#define IB335 ibit[334]
#define IB336 ibit[335]
#define IB337 ibit[336]
#define IB338 ibit[337]
#define IB339 ibit[338]
#define IB340 ibit[339]
#define IB341 ibit[340]
#define IB342 ibit[341]
#define IB343 ibit[342]
#define IB344 ibit[343]
#define IB345 ibit[344]
#define IB346 ibit[345]
#define IB347 ibit[346]
#define IB348 ibit[347]
#define IB349 ibit[348]
#define IB350 ibit[349]
#define IB351 ibit[350]
#define IB352 ibit[351]
#define IB353 ibit[352]
#define IB354 ibit[353]
#define IB355 ibit[354]
#define IB356 ibit[355]
#define IB357 ibit[356]
#define IB358 ibit[357]
#define IB359 ibit[358]
#define IB360 ibit[359]
#define IB361 ibit[360]
#define IB362 ibit[361]
#define IB363 ibit[362]
#define IB364 ibit[363]
#define IB365 ibit[364]
#define IB366 ibit[365]
#define IB367 ibit[366]
#define IB368 ibit[367]
#define IB369 ibit[368]
#define IB370 ibit[369]
#define IB371 ibit[370]
#define IB372 ibit[371]
#define IB373 ibit[372]
#define IB374 ibit[373]
#define IB375 ibit[374]
#define IB376 ibit[375]
#define IB377 ibit[376]
#define IB378 ibit[377]
#define IB379 ibit[378]
#define IB380 ibit[379]
#define IB381 ibit[380]
#define IB382 ibit[381]
#define IB383 ibit[382]
#define IB384 ibit[383]
#define IB385 ibit[384]
#define IB386 ibit[385]
#define IB387 ibit[386]
#define IB388 ibit[387]
#define IB389 ibit[388]
#define IB390 ibit[389]
#define IB391 ibit[390]
#define IB392 ibit[391]
#define IB393 ibit[392]
#define IB394 ibit[393]
#define IB395 ibit[394]
#define IB396 ibit[395]
#define IB397 ibit[396]
#define IB398 ibit[397]
#define IB399 ibit[398]
#define IB400 ibit[399]
#define IB401 ibit[400]
#define IB402 ibit[401]
#define IB403 ibit[402]
#define IB404 ibit[403]
#define IB405 ibit[404]
#define IB406 ibit[405]
#define IB407 ibit[406]
#define IB408 ibit[407]
#define IB409 ibit[408]
#define IB410 ibit[409]
#define IB411 ibit[410]
#define IB412 ibit[411]
#define IB413 ibit[412]
#define IB414 ibit[413]
#define IB415 ibit[414]
#define IB416 ibit[415]
#define IB417 ibit[416]
#define IB418 ibit[417]
#define IB419 ibit[418]
#define IB420 ibit[419]
#define IB421 ibit[420]
#define IB422 ibit[421]
#define IB423 ibit[422]
#define IB424 ibit[423]
#define IB425 ibit[424]
#define IB426 ibit[425]
#define IB427 ibit[426]
#define IB428 ibit[427]
#define IB429 ibit[428]
#define IB430 ibit[429]
#define IB431 ibit[430]
#define IB432 ibit[431]
#define IB433 ibit[432]
#define IB434 ibit[433]
#define IB435 ibit[434]
#define IB436 ibit[435]
#define IB437 ibit[436]
#define IB438 ibit[437]
#define IB439 ibit[438]
#define IB440 ibit[439]
#define IB441 ibit[440]
#define IB442 ibit[441]
#define IB443 ibit[442]
#define IB444 ibit[443]
#define IB445 ibit[444]
#define IB446 ibit[445]
#define IB447 ibit[446]
#define IB448 ibit[447]
#define IB449 ibit[448]
#define IB450 ibit[449]
#define IB451 ibit[450]
#define IB452 ibit[451]
#define IB453 ibit[452]
#define IB454 ibit[453]
#define IB455 ibit[454]
#define IB456 ibit[455]
#define IB457 ibit[456]
#define IB458 ibit[457]
#define IB459 ibit[458]
#define IB460 ibit[459]
#define IB461 ibit[460]
#define IB462 ibit[461]
#define IB463 ibit[462]
#define IB464 ibit[463]
#define IB465 ibit[464]
#define IB466 ibit[465]
#define IB467 ibit[466]
#define IB468 ibit[467]
#define IB469 ibit[468]
#define IB470 ibit[469]
#define IB471 ibit[470]
#define IB472 ibit[471]
#define IB473 ibit[472]
#define IB474 ibit[473]
#define IB475 ibit[474]
#define IB476 ibit[475]
#define IB477 ibit[476]
#define IB478 ibit[477]
#define IB479 ibit[478]
#define IB480 ibit[479]
#define IB481 ibit[480]
#define IB482 ibit[481]
#define IB483 ibit[482]
#define IB484 ibit[483]
#define IB485 ibit[484]
#define IB486 ibit[485]
#define IB487 ibit[486]
#define IB488 ibit[487]
#define IB489 ibit[488]
#define IB490 ibit[489]
#define IB491 ibit[490]
#define IB492 ibit[491]
#define IB493 ibit[492]
#define IB494 ibit[493]
#define IB495 ibit[494]
#define IB496 ibit[495]
#define IB497 ibit[496]
#define IB498 ibit[497]
#define IB499 ibit[498]
#define IB500 ibit[499]
#define IB501 ibit[500]
#define IB502 ibit[501]
#define IB503 ibit[502]
#define IB504 ibit[503]
#define IB505 ibit[504]
#define IB506 ibit[505]
#define IB507 ibit[506]
#define IB508 ibit[507]
#define IB509 ibit[508]
#define IB510 ibit[509]
#define IB511 ibit[510]
#define IB512 ibit[511]
#define IR1 ireg[0]
#define IR2 ireg[1]
#define IR3 ireg[2]
#define IR4 ireg[3]
#define IR5 ireg[4]
#define IR6 ireg[5]
#define IR7 ireg[6]
#define IR8 ireg[7]
#define IR9 ireg[8]
#define IR10 ireg[9]
#define IR11 ireg[10]
#define IR12 ireg[11]
#define IR13 ireg[12]
#define IR14 ireg[13]
#define IR15 ireg[14]
#define IR16 ireg[15]
#define IR17 ireg[16]
#define IR18 ireg[17]
#define IR19 ireg[18]
#define IR20 ireg[19]
#define IR21 ireg[20]
#define IR22 ireg[21]
#define IR23 ireg[22]
#define IR24 ireg[23]
#define IR25 ireg[24]
#define IR26 ireg[25]
#define IR27 ireg[26]
#define IR28 ireg[27]
#define IR29 ireg[28]
#define IR30 ireg[29]
#define IR31 ireg[30]
#define IR32 ireg[31]
#define IR33 ireg[32]
#define IR34 ireg[33]
#define IR35 ireg[34]
#define IR36 ireg[35]
#define IR37 ireg[36]
#define IR38 ireg[37]
#define IR39 ireg[38]
#define IR40 ireg[39]
#define IR41 ireg[40]
#define IR42 ireg[41]
#define IR43 ireg[42]
#define IR44 ireg[43]
#define IR45 ireg[44]
#define IR46 ireg[45]
#define IR47 ireg[46]
#define IR48 ireg[47]
#define IR49 ireg[48]
#define IR50 ireg[49]
#define IR51 ireg[50]
#define IR52 ireg[51]
#define IR53 ireg[52]
#define IR54 ireg[53]
#define IR55 ireg[54]
#define IR56 ireg[55]
#define IR57 ireg[56]
#define IR58 ireg[57]
#define IR59 ireg[58]
#define IR60 ireg[59]
#define IR61 ireg[60]
#define IR62 ireg[61]
#define IR63 ireg[62]
#define IR64 ireg[63]


#endif /* IODEF_H_ */
