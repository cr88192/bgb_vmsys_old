	.file	"disasm.c"
	.text
LC0:
	.ascii "a\0"
LC1:
	.ascii "ae\0"
LC2:
	.ascii "b\0"
LC3:
	.ascii "be\0"
LC4:
	.ascii "c\0"
LC5:
	.ascii "e\0"
LC6:
	.ascii "g\0"
LC7:
	.ascii "ge\0"
LC8:
	.ascii "l\0"
LC9:
	.ascii "le\0"
LC10:
	.ascii "na\0"
LC11:
	.ascii "nae\0"
LC12:
	.ascii "nb\0"
LC13:
	.ascii "nbe\0"
LC14:
	.ascii "nc\0"
LC15:
	.ascii "ne\0"
LC16:
	.ascii "ng\0"
LC17:
	.ascii "nge\0"
LC18:
	.ascii "nl\0"
LC19:
	.ascii "nle\0"
LC20:
	.ascii "no\0"
LC21:
	.ascii "np\0"
LC22:
	.ascii "ns\0"
LC23:
	.ascii "nz\0"
LC24:
	.ascii "o\0"
LC25:
	.ascii "p\0"
LC26:
	.ascii "pe\0"
LC27:
	.ascii "po\0"
LC28:
	.ascii "s\0"
LC29:
	.ascii "z\0"
	.data
	.align 32
_conditions:
	.long	LC0
	.long	LC1
	.long	LC2
	.long	LC3
	.long	LC4
	.long	LC5
	.long	LC6
	.long	LC7
	.long	LC8
	.long	LC9
	.long	LC10
	.long	LC11
	.long	LC12
	.long	LC13
	.long	LC14
	.long	LC15
	.long	LC16
	.long	LC17
	.long	LC18
	.long	LC19
	.long	LC20
	.long	LC21
	.long	LC22
	.long	LC23
	.long	LC24
	.long	LC25
	.long	LC26
	.long	LC27
	.long	LC28
	.long	LC29
	.text
LC30:
	.ascii "ah\0"
LC31:
	.ascii "al\0"
LC32:
	.ascii "ax\0"
LC33:
	.ascii "bh\0"
LC34:
	.ascii "bl\0"
LC35:
	.ascii "bp\0"
LC36:
	.ascii "bx\0"
LC37:
	.ascii "ch\0"
LC38:
	.ascii "cl\0"
LC39:
	.ascii "cr0\0"
LC40:
	.ascii "cr1\0"
LC41:
	.ascii "cr2\0"
LC42:
	.ascii "cr3\0"
LC43:
	.ascii "cr4\0"
LC44:
	.ascii "cr5\0"
LC45:
	.ascii "cr6\0"
LC46:
	.ascii "cr7\0"
LC47:
	.ascii "cs\0"
LC48:
	.ascii "cx\0"
LC49:
	.ascii "dh\0"
LC50:
	.ascii "di\0"
LC51:
	.ascii "dl\0"
LC52:
	.ascii "dr0\0"
LC53:
	.ascii "dr1\0"
LC54:
	.ascii "dr2\0"
LC55:
	.ascii "dr3\0"
LC56:
	.ascii "dr4\0"
LC57:
	.ascii "dr5\0"
LC58:
	.ascii "dr6\0"
LC59:
	.ascii "dr7\0"
LC60:
	.ascii "ds\0"
LC61:
	.ascii "dx\0"
LC62:
	.ascii "eax\0"
LC63:
	.ascii "ebp\0"
LC64:
	.ascii "ebx\0"
LC65:
	.ascii "ecx\0"
LC66:
	.ascii "edi\0"
LC67:
	.ascii "edx\0"
LC68:
	.ascii "es\0"
LC69:
	.ascii "esi\0"
LC70:
	.ascii "esp\0"
LC71:
	.ascii "fs\0"
LC72:
	.ascii "gs\0"
LC73:
	.ascii "mm0\0"
LC74:
	.ascii "mm1\0"
LC75:
	.ascii "mm2\0"
LC76:
	.ascii "mm3\0"
LC77:
	.ascii "mm4\0"
LC78:
	.ascii "mm5\0"
LC79:
	.ascii "mm6\0"
LC80:
	.ascii "mm7\0"
LC81:
	.ascii "segr6\0"
LC82:
	.ascii "segr7\0"
LC83:
	.ascii "si\0"
LC84:
	.ascii "sp\0"
LC85:
	.ascii "ss\0"
LC86:
	.ascii "st0\0"
LC87:
	.ascii "st1\0"
LC88:
	.ascii "st2\0"
LC89:
	.ascii "st3\0"
LC90:
	.ascii "st4\0"
LC91:
	.ascii "st5\0"
LC92:
	.ascii "st6\0"
LC93:
	.ascii "st7\0"
LC94:
	.ascii "tr0\0"
LC95:
	.ascii "tr1\0"
LC96:
	.ascii "tr2\0"
LC97:
	.ascii "tr3\0"
LC98:
	.ascii "tr4\0"
LC99:
	.ascii "tr5\0"
LC100:
	.ascii "tr6\0"
LC101:
	.ascii "tr7\0"
LC102:
	.ascii "xmm0\0"
LC103:
	.ascii "xmm1\0"
LC104:
	.ascii "xmm2\0"
LC105:
	.ascii "xmm3\0"
LC106:
	.ascii "xmm4\0"
LC107:
	.ascii "xmm5\0"
LC108:
	.ascii "xmm6\0"
LC109:
	.ascii "xmm7\0"
	.data
	.align 32
_reg_names:
	.long	LC30
	.long	LC31
	.long	LC32
	.long	LC33
	.long	LC34
	.long	LC35
	.long	LC36
	.long	LC37
	.long	LC38
	.long	LC39
	.long	LC40
	.long	LC41
	.long	LC42
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC48
	.long	LC49
	.long	LC50
	.long	LC51
	.long	LC52
	.long	LC53
	.long	LC54
	.long	LC55
	.long	LC56
	.long	LC57
	.long	LC58
	.long	LC59
	.long	LC60
	.long	LC61
	.long	LC62
	.long	LC63
	.long	LC64
	.long	LC65
	.long	LC66
	.long	LC67
	.long	LC68
	.long	LC69
	.long	LC70
	.long	LC71
	.long	LC72
	.long	LC73
	.long	LC74
	.long	LC75
	.long	LC76
	.long	LC77
	.long	LC78
	.long	LC79
	.long	LC80
	.long	LC81
	.long	LC82
	.long	LC83
	.long	LC84
	.long	LC85
	.long	LC86
	.long	LC87
	.long	LC88
	.long	LC89
	.long	LC90
	.long	LC91
	.long	LC92
	.long	LC93
	.long	LC94
	.long	LC95
	.long	LC96
	.long	LC97
	.long	LC98
	.long	LC99
	.long	LC100
	.long	LC101
	.long	LC102
	.long	LC103
	.long	LC104
	.long	LC105
	.long	LC106
	.long	LC107
	.long	LC108
	.long	LC109
	.text
LC110:
	.ascii "aaa\0"
LC111:
	.ascii "aad\0"
LC112:
	.ascii "aam\0"
LC113:
	.ascii "aas\0"
LC114:
	.ascii "adc\0"
LC115:
	.ascii "add\0"
LC116:
	.ascii "addpd\0"
LC117:
	.ascii "addps\0"
LC118:
	.ascii "addsd\0"
LC119:
	.ascii "addss\0"
LC120:
	.ascii "addsubpd\0"
LC121:
	.ascii "addsubps\0"
LC122:
	.ascii "and\0"
LC123:
	.ascii "andnpd\0"
LC124:
	.ascii "andnps\0"
LC125:
	.ascii "andpd\0"
LC126:
	.ascii "andps\0"
LC127:
	.ascii "arpl\0"
LC128:
	.ascii "bound\0"
LC129:
	.ascii "bsf\0"
LC130:
	.ascii "bsr\0"
LC131:
	.ascii "bswap\0"
LC132:
	.ascii "bt\0"
LC133:
	.ascii "btc\0"
LC134:
	.ascii "btr\0"
LC135:
	.ascii "bts\0"
LC136:
	.ascii "call\0"
LC137:
	.ascii "cbw\0"
LC138:
	.ascii "cdq\0"
LC139:
	.ascii "clc\0"
LC140:
	.ascii "cld\0"
LC141:
	.ascii "clflush\0"
LC142:
	.ascii "cli\0"
LC143:
	.ascii "clts\0"
LC144:
	.ascii "cmc\0"
LC145:
	.ascii "cmp\0"
LC146:
	.ascii "cmpeqpd\0"
LC147:
	.ascii "cmpeqps\0"
LC148:
	.ascii "cmpeqsd\0"
LC149:
	.ascii "cmpeqss\0"
LC150:
	.ascii "cmplepd\0"
LC151:
	.ascii "cmpleps\0"
LC152:
	.ascii "cmplesd\0"
LC153:
	.ascii "cmpless\0"
LC154:
	.ascii "cmpltpd\0"
LC155:
	.ascii "cmpltps\0"
LC156:
	.ascii "cmpltsd\0"
LC157:
	.ascii "cmpltss\0"
LC158:
	.ascii "cmpneqpd\0"
LC159:
	.ascii "cmpneqps\0"
LC160:
	.ascii "cmpneqsd\0"
LC161:
	.ascii "cmpneqss\0"
LC162:
	.ascii "cmpnlepd\0"
LC163:
	.ascii "cmpnleps\0"
LC164:
	.ascii "cmpnlesd\0"
LC165:
	.ascii "cmpnless\0"
LC166:
	.ascii "cmpnltpd\0"
LC167:
	.ascii "cmpnltps\0"
LC168:
	.ascii "cmpnltsd\0"
LC169:
	.ascii "cmpnltss\0"
LC170:
	.ascii "cmpordpd\0"
LC171:
	.ascii "cmpordps\0"
LC172:
	.ascii "cmpordsd\0"
LC173:
	.ascii "cmpordss\0"
LC174:
	.ascii "cmppd\0"
LC175:
	.ascii "cmpps\0"
LC176:
	.ascii "cmpsb\0"
LC177:
	.ascii "cmpsd\0"
LC178:
	.ascii "cmpss\0"
LC179:
	.ascii "cmpsw\0"
LC180:
	.ascii "cmpunordpd\0"
LC181:
	.ascii "cmpunordps\0"
LC182:
	.ascii "cmpunordsd\0"
LC183:
	.ascii "cmpunordss\0"
LC184:
	.ascii "cmpxchg\0"
LC185:
	.ascii "cmpxchg486\0"
LC186:
	.ascii "cmpxchg8b\0"
LC187:
	.ascii "comisd\0"
LC188:
	.ascii "comiss\0"
LC189:
	.ascii "cpuid\0"
LC190:
	.ascii "cvtdq2pd\0"
LC191:
	.ascii "cvtdq2ps\0"
LC192:
	.ascii "cvtpd2dq\0"
LC193:
	.ascii "cvtpd2pi\0"
LC194:
	.ascii "cvtpd2ps\0"
LC195:
	.ascii "cvtpi2pd\0"
LC196:
	.ascii "cvtpi2ps\0"
LC197:
	.ascii "cvtps2dq\0"
LC198:
	.ascii "cvtps2pd\0"
LC199:
	.ascii "cvtps2pi\0"
LC200:
	.ascii "cvtsd2si\0"
LC201:
	.ascii "cvtsd2ss\0"
LC202:
	.ascii "cvtsi2sd\0"
LC203:
	.ascii "cvtsi2ss\0"
LC204:
	.ascii "cvtss2sd\0"
LC205:
	.ascii "cvtss2si\0"
LC206:
	.ascii "cvttpd2dq\0"
LC207:
	.ascii "cvttpd2pi\0"
LC208:
	.ascii "cvttps2dq\0"
LC209:
	.ascii "cvttps2pi\0"
LC210:
	.ascii "cvttsd2si\0"
LC211:
	.ascii "cvttss2si\0"
LC212:
	.ascii "cwd\0"
LC213:
	.ascii "cwde\0"
LC214:
	.ascii "daa\0"
LC215:
	.ascii "das\0"
LC216:
	.ascii "db\0"
LC217:
	.ascii "dd\0"
LC218:
	.ascii "dec\0"
LC219:
	.ascii "div\0"
LC220:
	.ascii "divpd\0"
LC221:
	.ascii "divps\0"
LC222:
	.ascii "divsd\0"
LC223:
	.ascii "divss\0"
LC224:
	.ascii "dq\0"
LC225:
	.ascii "dt\0"
LC226:
	.ascii "dw\0"
LC227:
	.ascii "emms\0"
LC228:
	.ascii "enter\0"
LC229:
	.ascii "equ\0"
LC230:
	.ascii "f2xm1\0"
LC231:
	.ascii "fabs\0"
LC232:
	.ascii "fadd\0"
LC233:
	.ascii "faddp\0"
LC234:
	.ascii "fbld\0"
LC235:
	.ascii "fbstp\0"
LC236:
	.ascii "fchs\0"
LC237:
	.ascii "fclex\0"
LC238:
	.ascii "fcmovb\0"
LC239:
	.ascii "fcmovbe\0"
LC240:
	.ascii "fcmove\0"
LC241:
	.ascii "fcmovnb\0"
LC242:
	.ascii "fcmovnbe\0"
LC243:
	.ascii "fcmovne\0"
LC244:
	.ascii "fcmovnu\0"
LC245:
	.ascii "fcmovu\0"
LC246:
	.ascii "fcom\0"
LC247:
	.ascii "fcomi\0"
LC248:
	.ascii "fcomip\0"
LC249:
	.ascii "fcomp\0"
LC250:
	.ascii "fcompp\0"
LC251:
	.ascii "fcos\0"
LC252:
	.ascii "fdecstp\0"
LC253:
	.ascii "fdisi\0"
LC254:
	.ascii "fdiv\0"
LC255:
	.ascii "fdivp\0"
LC256:
	.ascii "fdivr\0"
LC257:
	.ascii "fdivrp\0"
LC258:
	.ascii "femms\0"
LC259:
	.ascii "feni\0"
LC260:
	.ascii "ffree\0"
LC261:
	.ascii "ffreep\0"
LC262:
	.ascii "fiadd\0"
LC263:
	.ascii "ficom\0"
LC264:
	.ascii "ficomp\0"
LC265:
	.ascii "fidiv\0"
LC266:
	.ascii "fidivr\0"
LC267:
	.ascii "fild\0"
LC268:
	.ascii "fimul\0"
LC269:
	.ascii "fincstp\0"
LC270:
	.ascii "finit\0"
LC271:
	.ascii "fist\0"
LC272:
	.ascii "fistp\0"
LC273:
	.ascii "fisttp\0"
LC274:
	.ascii "fisub\0"
LC275:
	.ascii "fisubr\0"
LC276:
	.ascii "fld\0"
LC277:
	.ascii "fld1\0"
LC278:
	.ascii "fldcw\0"
LC279:
	.ascii "fldenv\0"
LC280:
	.ascii "fldl2e\0"
LC281:
	.ascii "fldl2t\0"
LC282:
	.ascii "fldlg2\0"
LC283:
	.ascii "fldln2\0"
LC284:
	.ascii "fldpi\0"
LC285:
	.ascii "fldz\0"
LC286:
	.ascii "fmul\0"
LC287:
	.ascii "fmulp\0"
LC288:
	.ascii "fnclex\0"
LC289:
	.ascii "fndisi\0"
LC290:
	.ascii "fneni\0"
LC291:
	.ascii "fninit\0"
LC292:
	.ascii "fnop\0"
LC293:
	.ascii "fnsave\0"
LC294:
	.ascii "fnstcw\0"
LC295:
	.ascii "fnstenv\0"
LC296:
	.ascii "fnstsw\0"
LC297:
	.ascii "fpatan\0"
LC298:
	.ascii "fprem\0"
LC299:
	.ascii "fprem1\0"
LC300:
	.ascii "fptan\0"
LC301:
	.ascii "frndint\0"
LC302:
	.ascii "frstor\0"
LC303:
	.ascii "fsave\0"
LC304:
	.ascii "fscale\0"
LC305:
	.ascii "fsetpm\0"
LC306:
	.ascii "fsin\0"
LC307:
	.ascii "fsincos\0"
LC308:
	.ascii "fsqrt\0"
LC309:
	.ascii "fst\0"
LC310:
	.ascii "fstcw\0"
LC311:
	.ascii "fstenv\0"
LC312:
	.ascii "fstp\0"
LC313:
	.ascii "fstsw\0"
LC314:
	.ascii "fsub\0"
LC315:
	.ascii "fsubp\0"
LC316:
	.ascii "fsubr\0"
LC317:
	.ascii "fsubrp\0"
LC318:
	.ascii "ftst\0"
LC319:
	.ascii "fucom\0"
LC320:
	.ascii "fucomi\0"
LC321:
	.ascii "fucomip\0"
LC322:
	.ascii "fucomp\0"
LC323:
	.ascii "fucompp\0"
LC324:
	.ascii "fwait\0"
LC325:
	.ascii "fxam\0"
LC326:
	.ascii "fxch\0"
LC327:
	.ascii "fxrstor\0"
LC328:
	.ascii "fxsave\0"
LC329:
	.ascii "fxtract\0"
LC330:
	.ascii "fyl2x\0"
LC331:
	.ascii "fyl2xp1\0"
LC332:
	.ascii "haddpd\0"
LC333:
	.ascii "haddps\0"
LC334:
	.ascii "hlt\0"
LC335:
	.ascii "hsubpd\0"
LC336:
	.ascii "hsubps\0"
LC337:
	.ascii "ibts\0"
LC338:
	.ascii "icebp\0"
LC339:
	.ascii "idiv\0"
LC340:
	.ascii "imul\0"
LC341:
	.ascii "in\0"
LC342:
	.ascii "inc\0"
LC343:
	.ascii "incbin\0"
LC344:
	.ascii "insb\0"
LC345:
	.ascii "insd\0"
LC346:
	.ascii "insw\0"
LC347:
	.ascii "int\0"
LC348:
	.ascii "int01\0"
LC349:
	.ascii "int03\0"
LC350:
	.ascii "int1\0"
LC351:
	.ascii "int3\0"
LC352:
	.ascii "into\0"
LC353:
	.ascii "invd\0"
LC354:
	.ascii "invlpg\0"
LC355:
	.ascii "iret\0"
LC356:
	.ascii "iretd\0"
LC357:
	.ascii "iretw\0"
LC358:
	.ascii "jcxz\0"
LC359:
	.ascii "jecxz\0"
LC360:
	.ascii "jmp\0"
LC361:
	.ascii "jmpe\0"
LC362:
	.ascii "lahf\0"
LC363:
	.ascii "lar\0"
LC364:
	.ascii "lddqu\0"
LC365:
	.ascii "ldmxcsr\0"
LC366:
	.ascii "lds\0"
LC367:
	.ascii "lea\0"
LC368:
	.ascii "leave\0"
LC369:
	.ascii "les\0"
LC370:
	.ascii "lfence\0"
LC371:
	.ascii "lfs\0"
LC372:
	.ascii "lgdt\0"
LC373:
	.ascii "lgs\0"
LC374:
	.ascii "lidt\0"
LC375:
	.ascii "lldt\0"
LC376:
	.ascii "lmsw\0"
LC377:
	.ascii "loadall\0"
LC378:
	.ascii "loadall286\0"
LC379:
	.ascii "lodsb\0"
LC380:
	.ascii "lodsd\0"
LC381:
	.ascii "lodsw\0"
LC382:
	.ascii "loop\0"
LC383:
	.ascii "loope\0"
LC384:
	.ascii "loopne\0"
LC385:
	.ascii "loopnz\0"
LC386:
	.ascii "loopz\0"
LC387:
	.ascii "lsl\0"
LC388:
	.ascii "lss\0"
LC389:
	.ascii "ltr\0"
LC390:
	.ascii "maskmovdqu\0"
LC391:
	.ascii "maskmovq\0"
LC392:
	.ascii "maxpd\0"
LC393:
	.ascii "maxps\0"
LC394:
	.ascii "maxsd\0"
LC395:
	.ascii "maxss\0"
LC396:
	.ascii "mfence\0"
LC397:
	.ascii "minpd\0"
LC398:
	.ascii "minps\0"
LC399:
	.ascii "minsd\0"
LC400:
	.ascii "minss\0"
LC401:
	.ascii "monitor\0"
LC402:
	.ascii "mov\0"
LC403:
	.ascii "movapd\0"
LC404:
	.ascii "movaps\0"
LC405:
	.ascii "movd\0"
LC406:
	.ascii "movddup\0"
LC407:
	.ascii "movdq2q\0"
LC408:
	.ascii "movdqa\0"
LC409:
	.ascii "movdqu\0"
LC410:
	.ascii "movhlps\0"
LC411:
	.ascii "movhpd\0"
LC412:
	.ascii "movhps\0"
LC413:
	.ascii "movlhps\0"
LC414:
	.ascii "movlpd\0"
LC415:
	.ascii "movlps\0"
LC416:
	.ascii "movmskpd\0"
LC417:
	.ascii "movmskps\0"
LC418:
	.ascii "movntdq\0"
LC419:
	.ascii "movnti\0"
LC420:
	.ascii "movntpd\0"
LC421:
	.ascii "movntps\0"
LC422:
	.ascii "movntq\0"
LC423:
	.ascii "movq\0"
LC424:
	.ascii "movq2dq\0"
LC425:
	.ascii "movsb\0"
LC426:
	.ascii "movsd\0"
LC427:
	.ascii "movshdup\0"
LC428:
	.ascii "movsldup\0"
LC429:
	.ascii "movss\0"
LC430:
	.ascii "movsw\0"
LC431:
	.ascii "movsx\0"
LC432:
	.ascii "movupd\0"
LC433:
	.ascii "movups\0"
LC434:
	.ascii "movzx\0"
LC435:
	.ascii "mul\0"
LC436:
	.ascii "mulpd\0"
LC437:
	.ascii "mulps\0"
LC438:
	.ascii "mulsd\0"
LC439:
	.ascii "mulss\0"
LC440:
	.ascii "mwait\0"
LC441:
	.ascii "neg\0"
LC442:
	.ascii "nop\0"
LC443:
	.ascii "not\0"
LC444:
	.ascii "or\0"
LC445:
	.ascii "orpd\0"
LC446:
	.ascii "orps\0"
LC447:
	.ascii "out\0"
LC448:
	.ascii "outsb\0"
LC449:
	.ascii "outsd\0"
LC450:
	.ascii "outsw\0"
LC451:
	.ascii "packssdw\0"
LC452:
	.ascii "packsswb\0"
LC453:
	.ascii "packuswb\0"
LC454:
	.ascii "paddb\0"
LC455:
	.ascii "paddd\0"
LC456:
	.ascii "paddq\0"
LC457:
	.ascii "paddsb\0"
LC458:
	.ascii "paddsiw\0"
LC459:
	.ascii "paddsw\0"
LC460:
	.ascii "paddusb\0"
LC461:
	.ascii "paddusw\0"
LC462:
	.ascii "paddw\0"
LC463:
	.ascii "pand\0"
LC464:
	.ascii "pandn\0"
LC465:
	.ascii "pause\0"
LC466:
	.ascii "paveb\0"
LC467:
	.ascii "pavgb\0"
LC468:
	.ascii "pavgusb\0"
LC469:
	.ascii "pavgw\0"
LC470:
	.ascii "pcmpeqb\0"
LC471:
	.ascii "pcmpeqd\0"
LC472:
	.ascii "pcmpeqw\0"
LC473:
	.ascii "pcmpgtb\0"
LC474:
	.ascii "pcmpgtd\0"
LC475:
	.ascii "pcmpgtw\0"
LC476:
	.ascii "pdistib\0"
LC477:
	.ascii "pextrw\0"
LC478:
	.ascii "pf2id\0"
LC479:
	.ascii "pf2iw\0"
LC480:
	.ascii "pfacc\0"
LC481:
	.ascii "pfadd\0"
LC482:
	.ascii "pfcmpeq\0"
LC483:
	.ascii "pfcmpge\0"
LC484:
	.ascii "pfcmpgt\0"
LC485:
	.ascii "pfmax\0"
LC486:
	.ascii "pfmin\0"
LC487:
	.ascii "pfmul\0"
LC488:
	.ascii "pfnacc\0"
LC489:
	.ascii "pfpnacc\0"
LC490:
	.ascii "pfrcp\0"
LC491:
	.ascii "pfrcpit1\0"
LC492:
	.ascii "pfrcpit2\0"
LC493:
	.ascii "pfrsqit1\0"
LC494:
	.ascii "pfrsqrt\0"
LC495:
	.ascii "pfsub\0"
LC496:
	.ascii "pfsubr\0"
LC497:
	.ascii "pi2fd\0"
LC498:
	.ascii "pi2fw\0"
LC499:
	.ascii "pinsrw\0"
LC500:
	.ascii "pmachriw\0"
LC501:
	.ascii "pmaddwd\0"
LC502:
	.ascii "pmagw\0"
LC503:
	.ascii "pmaxsw\0"
LC504:
	.ascii "pmaxub\0"
LC505:
	.ascii "pminsw\0"
LC506:
	.ascii "pminub\0"
LC507:
	.ascii "pmovmskb\0"
LC508:
	.ascii "pmulhriw\0"
LC509:
	.ascii "pmulhrwa\0"
LC510:
	.ascii "pmulhrwc\0"
LC511:
	.ascii "pmulhuw\0"
LC512:
	.ascii "pmulhw\0"
LC513:
	.ascii "pmullw\0"
LC514:
	.ascii "pmuludq\0"
LC515:
	.ascii "pmvgezb\0"
LC516:
	.ascii "pmvlzb\0"
LC517:
	.ascii "pmvnzb\0"
LC518:
	.ascii "pmvzb\0"
LC519:
	.ascii "pop\0"
LC520:
	.ascii "popa\0"
LC521:
	.ascii "popad\0"
LC522:
	.ascii "popaw\0"
LC523:
	.ascii "popf\0"
LC524:
	.ascii "popfd\0"
LC525:
	.ascii "popfw\0"
LC526:
	.ascii "por\0"
LC527:
	.ascii "prefetch\0"
LC528:
	.ascii "prefetchnta\0"
LC529:
	.ascii "prefetcht0\0"
LC530:
	.ascii "prefetcht1\0"
LC531:
	.ascii "prefetcht2\0"
LC532:
	.ascii "prefetchw\0"
LC533:
	.ascii "psadbw\0"
LC534:
	.ascii "pshufd\0"
LC535:
	.ascii "pshufhw\0"
LC536:
	.ascii "pshuflw\0"
LC537:
	.ascii "pshufw\0"
LC538:
	.ascii "pslld\0"
LC539:
	.ascii "pslldq\0"
LC540:
	.ascii "psllq\0"
LC541:
	.ascii "psllw\0"
LC542:
	.ascii "psrad\0"
LC543:
	.ascii "psraw\0"
LC544:
	.ascii "psrld\0"
LC545:
	.ascii "psrldq\0"
LC546:
	.ascii "psrlq\0"
LC547:
	.ascii "psrlw\0"
LC548:
	.ascii "psubb\0"
LC549:
	.ascii "psubd\0"
LC550:
	.ascii "psubq\0"
LC551:
	.ascii "psubsb\0"
LC552:
	.ascii "psubsiw\0"
LC553:
	.ascii "psubsw\0"
LC554:
	.ascii "psubusb\0"
LC555:
	.ascii "psubusw\0"
LC556:
	.ascii "psubw\0"
LC557:
	.ascii "pswapd\0"
LC558:
	.ascii "punpckhbw\0"
LC559:
	.ascii "punpckhdq\0"
LC560:
	.ascii "punpckhqdq\0"
LC561:
	.ascii "punpckhwd\0"
LC562:
	.ascii "punpcklbw\0"
LC563:
	.ascii "punpckldq\0"
LC564:
	.ascii "punpcklqdq\0"
LC565:
	.ascii "punpcklwd\0"
LC566:
	.ascii "push\0"
LC567:
	.ascii "pusha\0"
LC568:
	.ascii "pushad\0"
LC569:
	.ascii "pushaw\0"
LC570:
	.ascii "pushf\0"
LC571:
	.ascii "pushfd\0"
LC572:
	.ascii "pushfw\0"
LC573:
	.ascii "pxor\0"
LC574:
	.ascii "rcl\0"
LC575:
	.ascii "rcpps\0"
LC576:
	.ascii "rcpss\0"
LC577:
	.ascii "rcr\0"
LC578:
	.ascii "rdmsr\0"
LC579:
	.ascii "rdpmc\0"
LC580:
	.ascii "rdshr\0"
LC581:
	.ascii "rdtsc\0"
LC582:
	.ascii "resb\0"
LC583:
	.ascii "resd\0"
LC584:
	.ascii "resq\0"
LC585:
	.ascii "rest\0"
LC586:
	.ascii "resw\0"
LC587:
	.ascii "ret\0"
LC588:
	.ascii "retf\0"
LC589:
	.ascii "retn\0"
LC590:
	.ascii "rol\0"
LC591:
	.ascii "ror\0"
LC592:
	.ascii "rsdc\0"
LC593:
	.ascii "rsldt\0"
LC594:
	.ascii "rsm\0"
LC595:
	.ascii "rsqrtps\0"
LC596:
	.ascii "rsqrtss\0"
LC597:
	.ascii "rsts\0"
LC598:
	.ascii "sahf\0"
LC599:
	.ascii "sal\0"
LC600:
	.ascii "salc\0"
LC601:
	.ascii "sar\0"
LC602:
	.ascii "sbb\0"
LC603:
	.ascii "scasb\0"
LC604:
	.ascii "scasd\0"
LC605:
	.ascii "scasw\0"
LC606:
	.ascii "sfence\0"
LC607:
	.ascii "sgdt\0"
LC608:
	.ascii "shl\0"
LC609:
	.ascii "shld\0"
LC610:
	.ascii "shr\0"
LC611:
	.ascii "shrd\0"
LC612:
	.ascii "shufpd\0"
LC613:
	.ascii "shufps\0"
LC614:
	.ascii "sidt\0"
LC615:
	.ascii "sldt\0"
LC616:
	.ascii "smi\0"
LC617:
	.ascii "smint\0"
LC618:
	.ascii "smintold\0"
LC619:
	.ascii "smsw\0"
LC620:
	.ascii "sqrtpd\0"
LC621:
	.ascii "sqrtps\0"
LC622:
	.ascii "sqrtsd\0"
LC623:
	.ascii "sqrtss\0"
LC624:
	.ascii "stc\0"
LC625:
	.ascii "std\0"
LC626:
	.ascii "sti\0"
LC627:
	.ascii "stmxcsr\0"
LC628:
	.ascii "stosb\0"
LC629:
	.ascii "stosd\0"
LC630:
	.ascii "stosw\0"
LC631:
	.ascii "str\0"
LC632:
	.ascii "sub\0"
LC633:
	.ascii "subpd\0"
LC634:
	.ascii "subps\0"
LC635:
	.ascii "subsd\0"
LC636:
	.ascii "subss\0"
LC637:
	.ascii "svdc\0"
LC638:
	.ascii "svldt\0"
LC639:
	.ascii "svts\0"
LC640:
	.ascii "syscall\0"
LC641:
	.ascii "sysenter\0"
LC642:
	.ascii "sysexit\0"
LC643:
	.ascii "sysret\0"
LC644:
	.ascii "test\0"
LC645:
	.ascii "ucomisd\0"
LC646:
	.ascii "ucomiss\0"
LC647:
	.ascii "ud0\0"
LC648:
	.ascii "ud1\0"
LC649:
	.ascii "ud2\0"
LC650:
	.ascii "umov\0"
LC651:
	.ascii "unpckhpd\0"
LC652:
	.ascii "unpckhps\0"
LC653:
	.ascii "unpcklpd\0"
LC654:
	.ascii "unpcklps\0"
LC655:
	.ascii "verr\0"
LC656:
	.ascii "verw\0"
LC657:
	.ascii "wait\0"
LC658:
	.ascii "wbinvd\0"
LC659:
	.ascii "wrmsr\0"
LC660:
	.ascii "wrshr\0"
LC661:
	.ascii "xadd\0"
LC662:
	.ascii "xbts\0"
LC663:
	.ascii "xchg\0"
LC664:
	.ascii "xlat\0"
LC665:
	.ascii "xlatb\0"
LC666:
	.ascii "xor\0"
LC667:
	.ascii "xorpd\0"
LC668:
	.ascii "xorps\0"
LC669:
	.ascii "xstore\0"
	.data
	.align 32
_insn_names:
	.long	LC110
	.long	LC111
	.long	LC112
	.long	LC113
	.long	LC114
	.long	LC115
	.long	LC116
	.long	LC117
	.long	LC118
	.long	LC119
	.long	LC120
	.long	LC121
	.long	LC122
	.long	LC123
	.long	LC124
	.long	LC125
	.long	LC126
	.long	LC127
	.long	LC128
	.long	LC129
	.long	LC130
	.long	LC131
	.long	LC132
	.long	LC133
	.long	LC134
	.long	LC135
	.long	LC136
	.long	LC137
	.long	LC138
	.long	LC139
	.long	LC140
	.long	LC141
	.long	LC142
	.long	LC143
	.long	LC144
	.long	LC145
	.long	LC146
	.long	LC147
	.long	LC148
	.long	LC149
	.long	LC150
	.long	LC151
	.long	LC152
	.long	LC153
	.long	LC154
	.long	LC155
	.long	LC156
	.long	LC157
	.long	LC158
	.long	LC159
	.long	LC160
	.long	LC161
	.long	LC162
	.long	LC163
	.long	LC164
	.long	LC165
	.long	LC166
	.long	LC167
	.long	LC168
	.long	LC169
	.long	LC170
	.long	LC171
	.long	LC172
	.long	LC173
	.long	LC174
	.long	LC175
	.long	LC176
	.long	LC177
	.long	LC178
	.long	LC179
	.long	LC180
	.long	LC181
	.long	LC182
	.long	LC183
	.long	LC184
	.long	LC185
	.long	LC186
	.long	LC187
	.long	LC188
	.long	LC189
	.long	LC190
	.long	LC191
	.long	LC192
	.long	LC193
	.long	LC194
	.long	LC195
	.long	LC196
	.long	LC197
	.long	LC198
	.long	LC199
	.long	LC200
	.long	LC201
	.long	LC202
	.long	LC203
	.long	LC204
	.long	LC205
	.long	LC206
	.long	LC207
	.long	LC208
	.long	LC209
	.long	LC210
	.long	LC211
	.long	LC212
	.long	LC213
	.long	LC214
	.long	LC215
	.long	LC216
	.long	LC217
	.long	LC218
	.long	LC219
	.long	LC220
	.long	LC221
	.long	LC222
	.long	LC223
	.long	LC224
	.long	LC225
	.long	LC226
	.long	LC227
	.long	LC228
	.long	LC229
	.long	LC230
	.long	LC231
	.long	LC232
	.long	LC233
	.long	LC234
	.long	LC235
	.long	LC236
	.long	LC237
	.long	LC238
	.long	LC239
	.long	LC240
	.long	LC241
	.long	LC242
	.long	LC243
	.long	LC244
	.long	LC245
	.long	LC246
	.long	LC247
	.long	LC248
	.long	LC249
	.long	LC250
	.long	LC251
	.long	LC252
	.long	LC253
	.long	LC254
	.long	LC255
	.long	LC256
	.long	LC257
	.long	LC258
	.long	LC259
	.long	LC260
	.long	LC261
	.long	LC262
	.long	LC263
	.long	LC264
	.long	LC265
	.long	LC266
	.long	LC267
	.long	LC268
	.long	LC269
	.long	LC270
	.long	LC271
	.long	LC272
	.long	LC273
	.long	LC274
	.long	LC275
	.long	LC276
	.long	LC277
	.long	LC278
	.long	LC279
	.long	LC280
	.long	LC281
	.long	LC282
	.long	LC283
	.long	LC284
	.long	LC285
	.long	LC286
	.long	LC287
	.long	LC288
	.long	LC289
	.long	LC290
	.long	LC291
	.long	LC292
	.long	LC293
	.long	LC294
	.long	LC295
	.long	LC296
	.long	LC297
	.long	LC298
	.long	LC299
	.long	LC300
	.long	LC301
	.long	LC302
	.long	LC303
	.long	LC304
	.long	LC305
	.long	LC306
	.long	LC307
	.long	LC308
	.long	LC309
	.long	LC310
	.long	LC311
	.long	LC312
	.long	LC313
	.long	LC314
	.long	LC315
	.long	LC316
	.long	LC317
	.long	LC318
	.long	LC319
	.long	LC320
	.long	LC321
	.long	LC322
	.long	LC323
	.long	LC324
	.long	LC325
	.long	LC326
	.long	LC327
	.long	LC328
	.long	LC329
	.long	LC330
	.long	LC331
	.long	LC332
	.long	LC333
	.long	LC334
	.long	LC335
	.long	LC336
	.long	LC337
	.long	LC338
	.long	LC339
	.long	LC340
	.long	LC341
	.long	LC342
	.long	LC343
	.long	LC344
	.long	LC345
	.long	LC346
	.long	LC347
	.long	LC348
	.long	LC349
	.long	LC350
	.long	LC351
	.long	LC352
	.long	LC353
	.long	LC354
	.long	LC355
	.long	LC356
	.long	LC357
	.long	LC358
	.long	LC359
	.long	LC360
	.long	LC361
	.long	LC362
	.long	LC363
	.long	LC364
	.long	LC365
	.long	LC366
	.long	LC367
	.long	LC368
	.long	LC369
	.long	LC370
	.long	LC371
	.long	LC372
	.long	LC373
	.long	LC374
	.long	LC375
	.long	LC376
	.long	LC377
	.long	LC378
	.long	LC379
	.long	LC380
	.long	LC381
	.long	LC382
	.long	LC383
	.long	LC384
	.long	LC385
	.long	LC386
	.long	LC387
	.long	LC388
	.long	LC389
	.long	LC390
	.long	LC391
	.long	LC392
	.long	LC393
	.long	LC394
	.long	LC395
	.long	LC396
	.long	LC397
	.long	LC398
	.long	LC399
	.long	LC400
	.long	LC401
	.long	LC402
	.long	LC403
	.long	LC404
	.long	LC405
	.long	LC406
	.long	LC407
	.long	LC408
	.long	LC409
	.long	LC410
	.long	LC411
	.long	LC412
	.long	LC413
	.long	LC414
	.long	LC415
	.long	LC416
	.long	LC417
	.long	LC418
	.long	LC419
	.long	LC420
	.long	LC421
	.long	LC422
	.long	LC423
	.long	LC424
	.long	LC425
	.long	LC426
	.long	LC427
	.long	LC428
	.long	LC429
	.long	LC430
	.long	LC431
	.long	LC432
	.long	LC433
	.long	LC434
	.long	LC435
	.long	LC436
	.long	LC437
	.long	LC438
	.long	LC439
	.long	LC440
	.long	LC441
	.long	LC442
	.long	LC443
	.long	LC444
	.long	LC445
	.long	LC446
	.long	LC447
	.long	LC448
	.long	LC449
	.long	LC450
	.long	LC451
	.long	LC452
	.long	LC453
	.long	LC454
	.long	LC455
	.long	LC456
	.long	LC457
	.long	LC458
	.long	LC459
	.long	LC460
	.long	LC461
	.long	LC462
	.long	LC463
	.long	LC464
	.long	LC465
	.long	LC466
	.long	LC467
	.long	LC468
	.long	LC469
	.long	LC470
	.long	LC471
	.long	LC472
	.long	LC473
	.long	LC474
	.long	LC475
	.long	LC476
	.long	LC477
	.long	LC478
	.long	LC479
	.long	LC480
	.long	LC481
	.long	LC482
	.long	LC483
	.long	LC484
	.long	LC485
	.long	LC486
	.long	LC487
	.long	LC488
	.long	LC489
	.long	LC490
	.long	LC491
	.long	LC492
	.long	LC493
	.long	LC494
	.long	LC495
	.long	LC496
	.long	LC497
	.long	LC498
	.long	LC499
	.long	LC500
	.long	LC501
	.long	LC502
	.long	LC503
	.long	LC504
	.long	LC505
	.long	LC506
	.long	LC507
	.long	LC508
	.long	LC509
	.long	LC510
	.long	LC511
	.long	LC512
	.long	LC513
	.long	LC514
	.long	LC515
	.long	LC516
	.long	LC517
	.long	LC518
	.long	LC519
	.long	LC520
	.long	LC521
	.long	LC522
	.long	LC523
	.long	LC524
	.long	LC525
	.long	LC526
	.long	LC527
	.long	LC528
	.long	LC529
	.long	LC530
	.long	LC531
	.long	LC532
	.long	LC533
	.long	LC534
	.long	LC535
	.long	LC536
	.long	LC537
	.long	LC538
	.long	LC539
	.long	LC540
	.long	LC541
	.long	LC542
	.long	LC543
	.long	LC544
	.long	LC545
	.long	LC546
	.long	LC547
	.long	LC548
	.long	LC549
	.long	LC550
	.long	LC551
	.long	LC552
	.long	LC553
	.long	LC554
	.long	LC555
	.long	LC556
	.long	LC557
	.long	LC558
	.long	LC559
	.long	LC560
	.long	LC561
	.long	LC562
	.long	LC563
	.long	LC564
	.long	LC565
	.long	LC566
	.long	LC567
	.long	LC568
	.long	LC569
	.long	LC570
	.long	LC571
	.long	LC572
	.long	LC573
	.long	LC574
	.long	LC575
	.long	LC576
	.long	LC577
	.long	LC578
	.long	LC579
	.long	LC580
	.long	LC581
	.long	LC582
	.long	LC583
	.long	LC584
	.long	LC585
	.long	LC586
	.long	LC587
	.long	LC588
	.long	LC589
	.long	LC590
	.long	LC591
	.long	LC592
	.long	LC593
	.long	LC594
	.long	LC595
	.long	LC596
	.long	LC597
	.long	LC598
	.long	LC599
	.long	LC600
	.long	LC601
	.long	LC602
	.long	LC603
	.long	LC604
	.long	LC605
	.long	LC606
	.long	LC607
	.long	LC608
	.long	LC609
	.long	LC610
	.long	LC611
	.long	LC612
	.long	LC613
	.long	LC614
	.long	LC615
	.long	LC616
	.long	LC617
	.long	LC618
	.long	LC619
	.long	LC620
	.long	LC621
	.long	LC622
	.long	LC623
	.long	LC624
	.long	LC625
	.long	LC626
	.long	LC627
	.long	LC628
	.long	LC629
	.long	LC630
	.long	LC631
	.long	LC632
	.long	LC633
	.long	LC634
	.long	LC635
	.long	LC636
	.long	LC637
	.long	LC638
	.long	LC639
	.long	LC640
	.long	LC641
	.long	LC642
	.long	LC643
	.long	LC644
	.long	LC645
	.long	LC646
	.long	LC647
	.long	LC648
	.long	LC649
	.long	LC650
	.long	LC651
	.long	LC652
	.long	LC653
	.long	LC654
	.long	LC655
	.long	LC656
	.long	LC657
	.long	LC658
	.long	LC659
	.long	LC660
	.long	LC661
	.long	LC662
	.long	LC663
	.long	LC664
	.long	LC665
	.long	LC666
	.long	LC667
	.long	LC668
	.long	LC669
	.text
LC670:
	.ascii "cmov\0"
LC671:
	.ascii "j\0"
LC672:
	.ascii "set\0"
	.data
	.align 4
_icn:
	.long	LC670
	.long	LC671
	.long	LC672
	.align 4
_ico:
	.long	560
	.long	561
	.long	562
	.text
	.align 32
_creg.0:
	.long	10
	.long	11
	.long	12
	.long	13
	.long	14
	.long	15
	.long	16
	.long	17
	.align 32
_dreg.1:
	.long	23
	.long	24
	.long	25
	.long	26
	.long	27
	.long	28
	.long	29
	.long	30
	.align 32
_fpureg.2:
	.long	57
	.long	58
	.long	59
	.long	60
	.long	61
	.long	62
	.long	63
	.long	64
	.align 32
_mmxreg.3:
	.long	44
	.long	45
	.long	46
	.long	47
	.long	48
	.long	49
	.long	50
	.long	51
	.align 32
_reg16.4:
	.long	3
	.long	19
	.long	32
	.long	7
	.long	55
	.long	6
	.long	54
	.long	21
	.align 32
_reg32.5:
	.long	33
	.long	36
	.long	38
	.long	35
	.long	41
	.long	34
	.long	40
	.long	37
	.align 32
_reg8.6:
	.long	2
	.long	9
	.long	22
	.long	5
	.long	1
	.long	8
	.long	20
	.long	4
	.align 32
_sreg.7:
	.long	39
	.long	18
	.long	56
	.long	31
	.long	42
	.long	43
	.long	52
	.long	53
	.align 32
_treg.8:
	.long	65
	.long	66
	.long	67
	.long	68
	.long	69
	.long	70
	.long	71
	.long	72
	.align 32
_xmmreg.9:
	.long	73
	.long	74
	.long	75
	.long	76
	.long	77
	.long	78
	.long	79
	.long	80
	.align 2
	.def	_whichreg;	.scl	3;	.type	32;	.endef
_whichreg:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	12(%ebp), %ebx
	movl	%ecx, %eax
	notl	%eax
	movl	$2, %edx
	testl	$2166785, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$3, %edx
	testl	$2166786, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$33, %edx
	testl	$2166788, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$22, %edx
	testl	$2363393, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$32, %edx
	testl	$2363394, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$38, %edx
	testl	$2363396, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$9, %edx
	testl	$2232321, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$19, %edx
	testl	$2232322, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$36, %edx
	testl	$2232324, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	movl	$57, %edx
	testl	$16779264, %eax
	je	L1
	movl	%ecx, %eax
	notl	%eax
	testl	$17305602, %eax
	jne	L12
	cmpl	$1, %ebx
	sete	%al
	movzbl	%al, %eax
	decl	%eax
	andl	$-18, %eax
	leal	18(%eax), %edx
	jmp	L1
L12:
	movl	%ecx, %eax
	notl	%eax
	testl	$34082818, %eax
	jne	L15
	testl	%ebx, %ebx
	je	L18
	cmpl	$2, %ebx
	je	L18
	movl	$0, %eax
	cmpl	$3, %ebx
	jne	L17
L18:
	movl	_sreg.7(,%ebx,4), %eax
L17:
	movl	%eax, %edx
	jmp	L1
L15:
	movl	%ecx, %eax
	notl	%eax
	testl	$67637250, %eax
	jne	L19
	leal	-4(%ebx), %eax
	jmp	L37
L19:
	movl	%ecx, %eax
	notl	%eax
	testl	$134746114, %eax
	jne	L22
	leal	-6(%ebx), %eax
L37:
	movl	$0, %edx
	cmpl	$1, %eax
	ja	L1
	jmp	L36
L22:
	movl	$0, %edx
	cmpl	$7, %ebx
	ja	L1
	movl	%ecx, %eax
	notl	%eax
	testl	$2097153, %eax
	jne	L26
	movl	_reg8.6(,%ebx,4), %edx
	jmp	L1
L26:
	movl	%ecx, %eax
	notl	%eax
	testl	$2097154, %eax
	jne	L27
	movl	_reg16.4(,%ebx,4), %edx
	jmp	L1
L27:
	movl	%ecx, %eax
	notl	%eax
	testl	$2097156, %eax
	jne	L28
	movl	_reg32.5(,%ebx,4), %edx
	jmp	L1
L28:
	movl	%ecx, %eax
	notl	%eax
	testl	$528386, %eax
	jne	L29
L36:
	movl	_sreg.7(,%ebx,4), %edx
	jmp	L1
L29:
	movl	%ecx, %eax
	notl	%eax
	testl	$135270404, %eax
	jne	L30
	movl	_creg.0(,%ebx,4), %edx
	jmp	L1
L30:
	movl	%ecx, %eax
	notl	%eax
	testl	$269488132, %eax
	jne	L31
	movl	_dreg.1(,%ebx,4), %edx
	jmp	L1
L31:
	movl	%ecx, %eax
	notl	%eax
	testl	$537923588, %eax
	jne	L32
	movl	_treg.8(,%ebx,4), %edx
	jmp	L1
L32:
	movl	%ecx, %eax
	notl	%eax
	testl	$16777216, %eax
	jne	L33
	movl	_fpureg.2(,%ebx,4), %edx
	jmp	L1
L33:
	movl	%ecx, %eax
	notl	%eax
	testl	$2101256, %eax
	jne	L34
	movl	_mmxreg.3(,%ebx,4), %edx
	jmp	L1
L34:
	movl	%ecx, %eax
	notl	%eax
	movl	$0, %edx
	testl	$2101264, %eax
	jne	L1
	movl	_xmmreg.9(,%ebx,4), %edx
L1:
	movl	%edx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.data
	.align 32
_conds.10:
	.long	24
	.long	20
	.long	4
	.long	14
	.long	29
	.long	23
	.long	10
	.long	0
	.long	28
	.long	22
	.long	26
	.long	27
	.long	8
	.long	18
	.long	16
	.long	6
	.text
	.align 2
	.def	_whichcond;	.scl	3;	.type	32;	.endef
_whichcond:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	_conds.10(,%eax,4), %eax
	movl	_conditions(,%eax,4), %eax
	popl	%ebp
	ret
	.align 2
	.def	_do_ea;	.scl	3;	.type	32;	.endef
_do_ea:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$8, %esp
	movl	8(%ebp), %edi
	movl	12(%ebp), %eax
	movl	20(%ebp), %edx
	movl	24(%ebp), %esi
	movl	%eax, %ebx
	sarl	$6, %ebx
	andl	$3, %ebx
	andl	$7, %eax
	cmpl	$3, %ebx
	jne	L40
	movl	%eax, 8(%esi)
	orl	$4, 28(%esi)
	jmp	L100
L40:
	movl	$0, 4(%esi)
	cmpl	$16, 16(%ebp)
	jne	L41
	movl	$-1, 8(%esi)
	movl	$-1, 12(%esi)
	movl	$1, 16(%esi)
	cmpl	$7, %eax
	ja	L42
	jmp	*L51(,%eax,4)
	.align 4
	.align 4
L51:
	.long	L43
	.long	L44
	.long	L45
	.long	L46
	.long	L47
	.long	L48
	.long	L49
	.long	L50
L43:
	movl	$7, 8(%esi)
	jmp	L108
L44:
	movl	$7, 8(%esi)
	jmp	L107
L45:
	movl	$6, 8(%esi)
L108:
	movl	$54, 12(%esi)
	jmp	L42
L46:
	movl	$6, 8(%esi)
L107:
	movl	$21, 12(%esi)
	jmp	L42
L47:
	movl	$54, 8(%esi)
	jmp	L42
L48:
	movl	$21, 8(%esi)
	jmp	L42
L49:
	movl	$6, 8(%esi)
	jmp	L42
L50:
	movl	$7, 8(%esi)
L42:
	cmpl	$6, %eax
	jne	L53
	testl	%ebx, %ebx
	jne	L53
	movl	$-1, 8(%esi)
	cmpl	$16, %edx
	je	L54
	movl	$16, 4(%esi)
L54:
	movl	$2, %ebx
L53:
	cmpl	$1, %ebx
	je	L102
	cmpl	$1, %ebx
	jle	L112
	cmpl	$2, %ebx
	jne	L100
	orl	$16, 28(%esi)
	movzbl	(%edi), %edx
	movl	%edx, 32(%esi)
	incl	%edi
	movzbl	(%edi), %eax
	sall	$8, %eax
	jmp	L111
L41:
	movl	$-1, 12(%esi)
	cmpl	$7, %eax
	ja	L63
	jmp	*L71(,%eax,4)
	.align 4
	.align 4
L71:
	.long	L64
	.long	L65
	.long	L66
	.long	L67
	.long	L63
	.long	L68
	.long	L69
	.long	L70
L64:
	movl	$33, 8(%esi)
	jmp	L63
L65:
	movl	$36, 8(%esi)
	jmp	L63
L66:
	movl	$38, 8(%esi)
	jmp	L63
L67:
	movl	$35, 8(%esi)
	jmp	L63
L68:
	movl	$34, 8(%esi)
	jmp	L63
L69:
	movl	$40, 8(%esi)
	jmp	L63
L70:
	movl	$37, 8(%esi)
L63:
	cmpl	$5, %eax
	jne	L73
	testl	%ebx, %ebx
	jne	L73
	movl	$-1, 8(%esi)
	cmpl	$32, %edx
	je	L74
	movl	$32, 4(%esi)
L74:
	movl	$2, %ebx
L73:
	cmpl	$4, %eax
	jne	L75
	movzbl	(%edi), %eax
	movb	%al, %dl
	shrb	$6, %dl
	movb	%dl, -17(%ebp)
	movb	%al, %dl
	shrb	$3, %dl
	andl	$7, %edx
	movl	%eax, %ecx
	andl	$7, %ecx
	movl	%ecx, -16(%ebp)
	incl	%edi
	movl	$1, %eax
	movzbl	-17(%ebp), %ecx
	sall	%cl, %eax
	movl	%eax, 16(%esi)
	cmpl	$7, %edx
	ja	L76
	jmp	*L85(,%edx,4)
	.align 4
	.align 4
L85:
	.long	L77
	.long	L78
	.long	L79
	.long	L80
	.long	L81
	.long	L82
	.long	L83
	.long	L84
L77:
	movl	$33, 12(%esi)
	jmp	L76
L78:
	movl	$36, 12(%esi)
	jmp	L76
L79:
	movl	$38, 12(%esi)
	jmp	L76
L80:
	movl	$35, 12(%esi)
	jmp	L76
L81:
	movl	$-1, 12(%esi)
	jmp	L76
L82:
	movl	$34, 12(%esi)
	jmp	L76
L83:
	movl	$40, 12(%esi)
	jmp	L76
L84:
	movl	$37, 12(%esi)
L76:
	cmpl	$7, -16(%ebp)
	ja	L75
	movl	-16(%ebp), %eax
	jmp	*L98(,%eax,4)
	.align 4
	.align 4
L98:
	.long	L88
	.long	L89
	.long	L90
	.long	L91
	.long	L92
	.long	L95
	.long	L93
	.long	L94
L88:
	movl	$33, 8(%esi)
	jmp	L75
L89:
	movl	$36, 8(%esi)
	jmp	L75
L90:
	movl	$38, 8(%esi)
	jmp	L75
L91:
	movl	$35, 8(%esi)
	jmp	L75
L92:
	movl	$41, 8(%esi)
	jmp	L75
L93:
	movl	$40, 8(%esi)
	jmp	L75
L94:
	movl	$37, 8(%esi)
	jmp	L75
L95:
	testl	%ebx, %ebx
	jne	L96
	movl	$2, %ebx
	movl	$-1, 8(%esi)
	jmp	L75
L96:
	movl	$34, 8(%esi)
L75:
	cmpl	$1, %ebx
	je	L102
	cmpl	$1, %ebx
	jg	L106
L112:
	testl	%ebx, %ebx
	je	L101
	jmp	L100
L106:
	cmpl	$2, %ebx
	je	L103
	jmp	L100
L101:
	orl	$64, 28(%esi)
	jmp	L100
L102:
	orl	$8, 28(%esi)
	movsbl	(%edi),%eax
	jmp	L110
L103:
	orl	$32, 28(%esi)
	movzbl	(%edi), %edx
	movl	%edx, 32(%esi)
	incl	%edi
	movzbl	(%edi), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, 32(%esi)
	incl	%edi
	movzbl	(%edi), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, 32(%esi)
	incl	%edi
	movzbl	(%edi), %eax
	sall	$24, %eax
L111:
	orl	%edx, %eax
L110:
	movl	%eax, 32(%esi)
	incl	%edi
L100:
	movl	%edi, %eax
	addl	$8, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.def	_matches;	.scl	3;	.type	32;	.endef
_matches:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	12(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	20(%eax), %edi
	movl	%ebx, -16(%ebp)
	movl	$0, -20(%ebp)
	movl	$0, -24(%ebp)
	movl	$0, -28(%ebp)
	cmpl	$242, 28(%ebp)
	jne	L114
	movl	$88, -28(%ebp)
	jmp	L115
L114:
	cmpl	$243, 28(%ebp)
	jne	L115
	movl	$86, -28(%ebp)
L115:
	cmpb	$0, (%edi)
	je	L226
L217:
	movzbl	(%edi), %esi
	incl	%edi
	leal	-1(%esi), %eax
	cmpl	$2, %eax
	ja	L120
	movl	%eax, %esi
	cmpl	$-1, %eax
	je	L120
L125:
	movzbl	(%ebx), %edx
	incl	%ebx
	movzbl	(%edi), %eax
	incl	%edi
	cmpb	%dl, %al
	jne	L209
	decl	%esi
	cmpl	$-1, %esi
	jne	L125
L120:
	cmpl	$4, %esi
	jne	L126
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$23, %eax
	je	L129
	cmpl	$23, %eax
	jg	L133
	cmpl	$7, %eax
	je	L128
	jmp	L209
L133:
	cmpl	$31, %eax
	je	L130
	jmp	L209
L128:
	movl	32(%ebp), %eax
	movl	$0, 44(%eax)
	jmp	L126
L129:
	movl	32(%ebp), %edx
	movl	$2, 44(%edx)
	jmp	L126
L130:
	movl	32(%ebp), %ecx
	movl	$3, 44(%ecx)
L126:
	cmpl	$5, %esi
	jne	L134
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$161, %eax
	je	L136
	cmpl	$169, %eax
	je	L137
	jmp	L209
L136:
	movl	32(%ebp), %eax
	movl	$4, 44(%eax)
	jmp	L134
L137:
	movl	32(%ebp), %edx
	movl	$5, 44(%edx)
L134:
	cmpl	$6, %esi
	jne	L140
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$14, %eax
	je	L143
	cmpl	$14, %eax
	jg	L148
	cmpl	$6, %eax
	je	L142
	jmp	L209
L148:
	cmpl	$22, %eax
	je	L144
	cmpl	$30, %eax
	je	L145
	jmp	L209
L142:
	movl	32(%ebp), %ecx
	movl	$0, 44(%ecx)
	jmp	L140
L143:
	movl	32(%ebp), %eax
	movl	$1, 44(%eax)
	jmp	L140
L144:
	movl	32(%ebp), %edx
	movl	$2, 44(%edx)
	jmp	L140
L145:
	movl	32(%ebp), %ecx
	movl	$3, 44(%ecx)
L140:
	cmpl	$7, %esi
	jne	L149
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$160, %eax
	je	L151
	cmpl	$168, %eax
	je	L152
	jmp	L209
L151:
	movl	32(%ebp), %eax
	movl	$4, 44(%eax)
	jmp	L149
L152:
	movl	32(%ebp), %edx
	movl	$5, 44(%edx)
L149:
	leal	-8(%esi), %eax
	cmpl	$2, %eax
	ja	L155
	movzbl	(%edi), %ecx
	incl	%edi
	movzbl	(%ebx), %edx
	incl	%ebx
	cmpl	%ecx, %edx
	jl	L209
	leal	7(%ecx), %eax
	cmpl	%eax, %edx
	jg	L209
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	subl	%ecx, %edx
	movl	%edx, -340(%eax)
	orl	$4, -320(%eax)
L155:
	cmpl	$15, %esi
	jne	L159
	movzbl	(%ebx), %eax
	incl	%ebx
	testb	%al, %al
	jne	L209
L159:
	leal	-12(%esi), %eax
	cmpl	$2, %eax
	ja	L161
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	movsbl	(%ebx),%edx
	movl	%edx, -508(%eax)
	incl	%ebx
	orl	$128, -512(%eax)
L161:
	leal	-16(%esi), %eax
	cmpl	$2, %eax
	ja	L162
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movzbl	(%ebx), %edx
	movl	32(%ebp), %ecx
	movl	%edx, -700(%ecx,%eax)
	incl	%ebx
L162:
	leal	-20(%esi), %eax
	cmpl	$2, %eax
	ja	L163
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movzbl	(%ebx), %edx
	movl	32(%ebp), %ecx
	movl	%edx, -892(%ecx,%eax)
	incl	%ebx
L163:
	leal	-24(%esi), %eax
	cmpl	$2, %eax
	ja	L164
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	movzbl	(%ebx), %ecx
	movl	%ecx, -1084(%eax)
	incl	%ebx
	movzbl	(%ebx), %edx
	sall	$8, %edx
	orl	%ecx, %edx
	movl	%edx, -1084(%eax)
	incl	%ebx
L164:
	leal	-28(%esi), %eax
	cmpl	$2, %eax
	ja	L165
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	leal	(%edx,%eax), %ecx
	movzbl	(%ebx), %edx
	movl	%edx, -1276(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, -1276(%ecx)
	incl	%ebx
	cmpl	$32, 20(%ebp)
	jne	L166
	movzbl	(%ebx), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, -1276(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -1276(%ecx)
	incl	%ebx
L166:
	movl	16(%ebp), %ecx
	cmpl	%ecx, 24(%ebp)
	je	L165
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	movl	%ecx, -1304(%edx,%eax)
L165:
	leal	-32(%esi), %eax
	cmpl	$2, %eax
	ja	L168
	leal	(%esi,%esi,2), %ecx
	sall	$4, %ecx
	addl	32(%ebp), %ecx
	movzbl	(%ebx), %edx
	movl	%edx, -1468(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, -1468(%ecx)
	incl	%ebx
	movzbl	(%ebx), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, -1468(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -1468(%ecx)
	incl	%ebx
L168:
	leal	-36(%esi), %eax
	cmpl	$2, %eax
	ja	L169
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	leal	(%edx,%eax), %ecx
	movzbl	(%ebx), %edx
	movl	%edx, -1660(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, -1660(%ecx)
	incl	%ebx
	cmpl	$32, 16(%ebp)
	jne	L170
	movzbl	(%ebx), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, -1660(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -1660(%ecx)
	incl	%ebx
L170:
	movl	16(%ebp), %ecx
	cmpl	%ecx, 24(%ebp)
	je	L169
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	movl	%ecx, -1688(%edx,%eax)
L169:
	leal	-40(%esi), %eax
	cmpl	$2, %eax
	ja	L172
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	movsbl	(%ebx),%edx
	movl	%edx, -1852(%eax)
	incl	%ebx
	orl	$1, -1856(%eax)
L172:
	leal	-48(%esi), %eax
	cmpl	$2, %eax
	ja	L173
	leal	(%esi,%esi,2), %edx
	sall	$4, %edx
	addl	32(%ebp), %edx
	movzbl	(%ebx), %ecx
	movl	%ecx, -2236(%edx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%ecx, %eax
	movl	%eax, -2236(%edx)
	incl	%ebx
	movl	-2240(%edx), %eax
	orl	$1, %eax
	andl	$-3, %eax
	movl	%eax, -2240(%edx)
L173:
	leal	-52(%esi), %eax
	cmpl	$2, %eax
	ja	L174
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	leal	(%edx,%eax), %ecx
	movzbl	(%ebx), %edx
	movl	%edx, -2428(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, -2428(%ecx)
	incl	%ebx
	cmpl	$32, 20(%ebp)
	jne	L175
	movzbl	(%ebx), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, -2428(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -2428(%ecx)
	incl	%ebx
	orl	$2, -2432(%ecx)
	jmp	L176
L175:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %ecx
	andl	$-3, -2432(%ecx,%eax)
L176:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	orl	$1, -2432(%eax)
	movl	20(%ebp), %edx
	cmpl	%edx, 24(%ebp)
	je	L174
	leal	-2460(%eax), %edx
	movl	-2460(%eax), %eax
	andl	$-256, %eax
	cmpl	$16, 20(%ebp)
	jne	L178
	orl	$2, %eax
	jmp	L179
L178:
	orl	$4, %eax
L179:
	movl	%eax, (%edx)
L174:
	leal	-56(%esi), %eax
	cmpl	$2, %eax
	ja	L180
	leal	(%esi,%esi,2), %ecx
	sall	$4, %ecx
	addl	32(%ebp), %ecx
	movzbl	(%ebx), %edx
	movl	%edx, -2620(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, -2620(%ecx)
	incl	%ebx
	movzbl	(%ebx), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, -2620(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -2620(%ecx)
	incl	%ebx
	orl	$3, -2624(%ecx)
L180:
	leal	-64(%esi), %eax
	cmpl	$23, %eax
	ja	L181
	movzbl	(%ebx), %ecx
	incl	%ebx
	movl	%esi, %eax
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	movl	%ecx, %edx
	sarl	$3, %edx
	andl	$7, %edx
	movl	%edx, 44(%eax)
	orl	$4, 64(%eax)
	movl	%ebx, (%esp)
	movl	%ecx, 4(%esp)
	movl	16(%ebp), %ecx
	movl	%ecx, 8(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	%esi, %eax
	sarl	$3, %eax
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	leal	36(%eax,%edx), %eax
	movl	%eax, 16(%esp)
	call	_do_ea
	movl	%eax, %ebx
L181:
	leal	-88(%esi), %eax
	cmpl	$2, %eax
	ja	L182
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	addl	32(%ebp), %eax
	movzbl	(%ebx), %ecx
	movl	%ecx, -4156(%eax)
	incl	%ebx
	movzbl	(%ebx), %edx
	sall	$8, %edx
	orl	%ecx, %edx
	movl	%edx, -4156(%eax)
	incl	%ebx
L182:
	leal	-96(%esi), %eax
	cmpl	$2, %eax
	ja	L183
	leal	(%esi,%esi,2), %ecx
	sall	$4, %ecx
	addl	32(%ebp), %ecx
	movzbl	(%ebx), %edx
	movl	%edx, -4540(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$8, %eax
	orl	%edx, %eax
	movl	%eax, -4540(%ecx)
	incl	%ebx
	movzbl	(%ebx), %edx
	sall	$16, %edx
	orl	%eax, %edx
	movl	%edx, -4540(%ecx)
	incl	%ebx
	movzbl	(%ebx), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -4540(%ecx)
	incl	%ebx
L183:
	leal	-128(%esi), %eax
	cmpl	$63, %eax
	ja	L184
	movzbl	(%ebx), %ecx
	incl	%ebx
	movl	%ecx, %eax
	sarl	$3, %eax
	andl	$7, %eax
	movl	%esi, %edx
	andl	$7, %edx
	cmpl	%edx, %eax
	jne	L209
	movl	%ebx, (%esp)
	movl	%ecx, 4(%esp)
	movl	16(%ebp), %ecx
	movl	%ecx, 8(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	%esi, %eax
	sarl	$3, %eax
	andl	$7, %eax
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	leal	36(%eax,%edx), %eax
	movl	%eax, 16(%esp)
	call	_do_ea
	movl	%eax, %ebx
L184:
	leal	-192(%esi), %eax
	cmpl	$2, %eax
	ja	L186
	cmpl	$0, 16(%ebp)
	je	L187
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %ecx
	orl	$2, -9152(%ecx,%eax)
	jmp	L188
L187:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	32(%ebp), %edx
	andl	$-3, -9152(%edx,%eax)
L188:
	movl	$1, -20(%ebp)
L186:
	cmpl	$200, %esi
	jne	L189
	movl	$0, %eax
	cmpl	$32, 16(%ebp)
	je	L113
	movl	$1, -20(%ebp)
L189:
	cmpl	$201, %esi
	jne	L192
	movl	$0, %eax
	cmpl	$16, 16(%ebp)
	je	L113
	movl	$1, -20(%ebp)
L192:
	cmpl	$202, %esi
	jne	L195
	movl	$0, %eax
	movl	24(%ebp), %ecx
	cmpl	%ecx, 16(%ebp)
	jne	L113
	movl	$1, -20(%ebp)
L195:
	cmpl	$208, %esi
	jne	L198
	movl	$0, %eax
	cmpl	$32, 20(%ebp)
	je	L113
	movl	$1, -24(%ebp)
L198:
	cmpl	$209, %esi
	jne	L201
	movl	$0, %eax
	cmpl	$16, 20(%ebp)
	je	L113
	movl	$1, -24(%ebp)
L201:
	cmpl	$210, %esi
	jne	L204
	movl	$0, %eax
	movl	24(%ebp), %edx
	cmpl	%edx, 20(%ebp)
	jne	L113
	movl	$1, -24(%ebp)
L204:
	cmpl	$216, %esi
	jne	L207
	movzbl	(%edi), %ecx
	incl	%edi
	movzbl	(%ebx), %edx
	incl	%ebx
	cmpl	%ecx, %edx
	jl	L209
	leal	15(%ecx), %eax
	cmpl	%eax, %edx
	jle	L208
L209:
	movl	$0, %eax
	jmp	L113
L208:
	movl	%edx, %eax
	subl	%ecx, %eax
	movl	32(%ebp), %ecx
	movl	%eax, 28(%ecx)
L207:
	cmpl	$217, %esi
	jne	L211
	movl	$0, %eax
	cmpl	$0, 28(%ebp)
	jne	L113
L211:
	cmpl	$218, %esi
	jne	L213
	cmpl	$86, -28(%ebp)
	jne	L213
	movl	$87, -28(%ebp)
L213:
	cmpl	$219, %esi
	jne	L117
	movl	$0, %eax
	cmpl	$243, 28(%ebp)
	jne	L113
	movl	$0, -28(%ebp)
L117:
	cmpb	$0, (%edi)
	jne	L217
L226:
	movl	32(%ebp), %eax
	movl	$0, 20(%eax)
	cmpl	$0, -28(%ebp)
	je	L218
	movl	-28(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	$1, 20(%eax)
L218:
	cmpl	$0, -20(%ebp)
	jne	L219
	movl	24(%ebp), %ecx
	cmpl	%ecx, 16(%ebp)
	je	L219
	movl	32(%ebp), %eax
	movl	20(%eax), %edx
	leal	1(%edx), %eax
	movl	32(%ebp), %ecx
	movl	%eax, 20(%ecx)
	cmpl	$16, 16(%ebp)
	setne	%al
	movzbl	%al, %eax
	addl	$81, %eax
	movl	%eax, 4(%ecx,%edx,4)
L219:
	cmpl	$0, -24(%ebp)
	jne	L222
	movl	24(%ebp), %eax
	cmpl	%eax, 20(%ebp)
	je	L222
	movl	32(%ebp), %ecx
	movl	20(%ecx), %edx
	leal	1(%edx), %eax
	movl	%eax, 20(%ecx)
	cmpl	$16, 20(%ebp)
	setne	%al
	movzbl	%al, %eax
	addl	$84, %eax
	movl	%eax, 4(%ecx,%edx,4)
L222:
	movl	%ebx, %eax
	subl	-16(%ebp), %eax
L113:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC673:
	.ascii "lock \0"
LC674:
	.ascii "rep \0"
LC675:
	.ascii "repe \0"
LC676:
	.ascii "repne \0"
LC677:
	.ascii "a16 \0"
LC678:
	.ascii "a32 \0"
LC679:
	.ascii "o16 \0"
LC680:
	.ascii "o32 \0"
LC681:
	.ascii "%s%s\0"
LC682:
	.ascii "%s\0"
LC683:
	.ascii "to \0"
LC684:
	.ascii "byte \0"
LC685:
	.ascii "word \0"
LC686:
	.ascii "dword \0"
LC687:
	.ascii "near \0"
LC688:
	.ascii "short \0"
LC689:
	.ascii "0x%lx\0"
LC690:
	.ascii "[%s%s%s0x%lx]\0"
LC691:
	.ascii "\0"
LC692:
	.ascii ":\0"
LC693:
	.ascii "qword \0"
LC694:
	.ascii "tword \0"
LC695:
	.ascii "far \0"
LC696:
	.ascii "%s:\0"
LC697:
	.ascii "*%d\0"
LC698:
	.ascii "%c0x%lx\0"
LC699:
	.ascii "<operand%d>\0"
	.align 2
.globl _disasm
	.def	_disasm;	.scl	2;	.type	32;	.endef
_disasm:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$524, %esp
	movl	8(%ebp), %ebx
	movl	$0, -456(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -472(%ebp)
	movl	%eax, -492(%ebp)
	movl	$0, -460(%ebp)
	movl	$0, -468(%ebp)
	movl	$0, -464(%ebp)
	movl	%ebx, -480(%ebp)
L240:
	movzbl	(%ebx), %eax
	addb	$14, %al
	cmpb	$1, %al
	ja	L243
	movzbl	(%ebx), %edx
	movl	%edx, -464(%ebp)
	jmp	L396
L243:
	cmpb	$-16, (%ebx)
	jne	L245
	movl	$240, -468(%ebp)
	jmp	L396
L245:
	cmpb	$46, (%ebx)
	je	L248
	cmpb	$54, (%ebx)
	je	L248
	cmpb	$62, (%ebx)
	je	L248
	cmpb	$38, (%ebx)
	je	L248
	cmpb	$100, (%ebx)
	je	L248
	cmpb	$101, (%ebx)
	jne	L247
L248:
	movzbl	(%ebx), %eax
	incl	%ebx
	cmpl	$62, %eax
	je	L252
	cmpl	$62, %eax
	jg	L258
	cmpl	$46, %eax
	je	L250
	cmpl	$46, %eax
	jg	L259
	cmpl	$38, %eax
	je	L253
	jmp	L240
L259:
	cmpl	$54, %eax
	je	L251
	jmp	L240
L258:
	cmpl	$100, %eax
	je	L254
	cmpl	$101, %eax
	je	L255
	jmp	L240
L250:
	movl	$LC47, -460(%ebp)
	jmp	L240
L251:
	movl	$LC85, -460(%ebp)
	jmp	L240
L252:
	movl	$LC60, -460(%ebp)
	jmp	L240
L253:
	movl	$LC68, -460(%ebp)
	jmp	L240
L254:
	movl	$LC71, -460(%ebp)
	jmp	L240
L255:
	movl	$LC72, -460(%ebp)
	jmp	L240
L247:
	cmpb	$102, (%ebx)
	jne	L261
	movl	$48, %eax
	subl	16(%ebp), %eax
	movl	%eax, -472(%ebp)
	jmp	L396
L261:
	cmpb	$103, (%ebx)
	jne	L241
	movl	$48, %eax
	subl	16(%ebp), %eax
	movl	%eax, -492(%ebp)
L396:
	incl	%ebx
	jmp	L240
L241:
	cmpl	$16, 16(%ebp)
	setne	%al
	movzbl	%al, %eax
	addl	%eax, %eax
	movl	%eax, -96(%ebp)
	movl	%eax, -144(%ebp)
	movl	%eax, -192(%ebp)
	movl	%eax, -72(%ebp)
	movl	%eax, -120(%ebp)
	movl	%eax, -168(%ebp)
	movl	$-1, -204(%ebp)
	movl	$-1, -488(%ebp)
	movl	$0, -448(%ebp)
	movzbl	(%ebx), %eax
	movl	_itable(,%eax,4), %eax
	movl	%eax, -444(%ebp)
	cmpl	$0, (%eax)
	je	L385
L284:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	movl	%eax, (%esp)
	movl	%ebx, 4(%esp)
	movl	-492(%ebp), %edi
	movl	%edi, 8(%esp)
	movl	-472(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	-464(%ebp), %ecx
	movl	%ecx, 20(%esp)
	leal	-232(%ebp), %eax
	movl	%eax, 24(%esp)
	call	_matches
	movl	%eax, -452(%ebp)
	testl	%eax, %eax
	je	L269
	movl	$1, -484(%ebp)
	movl	$0, %esi
	movl	-444(%ebp), %edi
	movl	(%edi), %eax
	movl	%eax, %edx
	cmpl	4(%eax), %esi
	jge	L273
L281:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	testb	$4, -168(%ebp,%eax)
	je	L278
	movl	8(%edx,%esi,4), %eax
	notl	%eax
	testl	$2113536, %eax
	je	L277
L278:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	testb	$4, -168(%ebp,%eax)
	jne	L279
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	8(%eax,%esi,4), %edx
	movl	%edx, %eax
	notl	%eax
	testl	$2101248, %eax
	jne	L279
	testl	$458752, %edx
	je	L277
L279:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testl	$16781312, 8(%eax,%esi,4)
	jne	L280
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	testb	$4, -168(%ebp,%eax)
	je	L274
L280:
	movl	-444(%ebp), %edi
	movl	(%edi), %eax
	movl	8(%eax,%esi,4), %eax
	movl	%eax, (%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-188(%ebp,%eax), %eax
	movl	%eax, 4(%esp)
	call	_whichreg
	testl	%eax, %eax
	jne	L274
L277:
	movl	$0, -484(%ebp)
	jmp	L273
L274:
	incl	%esi
	movl	-444(%ebp), %eax
	movl	(%eax), %edx
	cmpl	4(%edx), %esi
	jl	L281
L273:
	cmpl	$0, -484(%ebp)
	je	L269
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	24(%eax), %eax
	andl	$-268304640, %eax
	xorl	28(%ebp), %eax
	cmpl	-488(%ebp), %eax
	jae	L269
	movl	%eax, -488(%ebp)
	movl	%edx, -448(%ebp)
	movl	-452(%ebp), %ecx
	movl	%ecx, -456(%ebp)
	leal	-440(%ebp), %eax
	leal	-232(%ebp), %esi
	cld
	movl	$49, %ecx
	movl	%eax, %edi
	rep
	movsl
L269:
	addl	$4, -444(%ebp)
	movl	-444(%ebp), %eax
	cmpl	$0, (%eax)
	jne	L284
L385:
	movl	$0, %eax
	cmpl	$0, -448(%ebp)
	je	L239
	movl	-448(%ebp), %edx
	movl	%edx, -444(%ebp)
	movl	-456(%ebp), %ecx
	movl	%ecx, -452(%ebp)
	movl	$0, %edi
	cmpl	$0, -468(%ebp)
	je	L286
	movl	12(%ebp), %edi
	movl	%edi, (%esp)
	movl	$LC673, 4(%esp)
	call	_sprintf
	movl	%eax, %edi
L286:
	movl	$0, %esi
	cmpl	-420(%ebp), %esi
	jge	L388
L301:
	movl	-436(%ebp,%esi,4), %eax
	subl	$81, %eax
	cmpl	$7, %eax
	ja	L289
	jmp	*L299(,%eax,4)
	.align 4
	.align 4
L299:
	.long	L295
	.long	L296
	.long	L289
	.long	L297
	.long	L298
	.long	L292
	.long	L293
	.long	L294
L292:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC674, 4(%esp)
	jmp	L397
L293:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC675, 4(%esp)
	jmp	L397
L294:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC676, 4(%esp)
	jmp	L397
L295:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC677, 4(%esp)
	jmp	L397
L296:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC678, 4(%esp)
	jmp	L397
L297:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC679, 4(%esp)
	jmp	L397
L298:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC680, 4(%esp)
L397:
	call	_sprintf
	addl	%eax, %edi
L289:
	incl	%esi
	cmpl	-420(%ebp), %esi
	jl	L301
L388:
	movl	$0, %esi
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	$_ico, %edx
	movl	(%eax), %eax
L307:
	cmpl	(%edx,%esi,4), %eax
	je	L395
	incl	%esi
	cmpl	$2, %esi
	jbe	L307
	jmp	L394
L395:
	movl	-412(%ebp), %eax
	movl	%eax, (%esp)
	call	_whichcond
	movl	12(%ebp), %edx
	addl	%edi, %edx
	movl	%edx, (%esp)
	movl	$LC681, 4(%esp)
	movl	_icn(,%esi,4), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 12(%esp)
	call	_sprintf
	addl	%eax, %edi
	cmpl	$2, %esi
	jbe	L308
L394:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC682, 4(%esp)
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	movl	(%eax), %eax
	movl	_insn_names(,%eax,4), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	addl	%eax, %edi
L308:
	movl	$0, -476(%ebp)
	movl	%ebx, %eax
	subl	-480(%ebp), %eax
	addl	%eax, -452(%ebp)
	movl	$0, %esi
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	cmpl	4(%eax), %esi
	jge	L391
L378:
	movl	%edi, %edx
	incl	%edi
	movb	$58, %al
	cmpl	$0, -476(%ebp)
	jne	L314
	movb	$32, %al
	testl	%esi, %esi
	je	L314
	movb	$44, %al
L314:
	movl	12(%ebp), %ecx
	movb	%al, (%edx,%ecx)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	leal	-24(%ebp), %edx
	addl	%edx, %eax
	movl	-352(%eax), %ecx
	testl	$1, %ecx
	je	L317
	leal	-352(%eax), %edx
	movl	20(%ebp), %eax
	addl	-452(%ebp), %eax
	addl	4(%edx), %eax
	movl	%eax, 4(%edx)
	testl	$2, %ecx
	jne	L318
	andl	$65535, %eax
	movl	%eax, 4(%edx)
L318:
	cmpl	$0, 24(%ebp)
	je	L317
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-372(%ebp,%eax), %eax
	movl	%eax, (%esp)
	movl	$0, 4(%esp)
	call	_add_sync
L317:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	movl	8(%eax,%esi,4), %edx
	testl	$512, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, -476(%ebp)
	testl	$16781312, %edx
	jne	L323
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	testb	$4, -376(%ebp,%eax)
	je	L322
L323:
	leal	(%esi,%esi,2), %ebx
	sall	$4, %ebx
	leal	-408(%ebp,%ebx), %ebx
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	8(%eax,%esi,4), %eax
	movl	%eax, (%esp)
	movl	12(%ebx), %eax
	movl	%eax, 4(%esp)
	call	_whichreg
	movl	%eax, 12(%ebx)
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testb	$1, 9(%eax,%esi,4)
	je	L324
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC683, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L324:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC682, 4(%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-396(%ebp,%eax), %eax
	movl	_reg_names-4(,%eax,4), %eax
	jmp	L403
L322:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	8(%eax,%esi,4), %eax
	notl	%eax
	testl	$8396800, %eax
	jne	L326
	movl	12(%ebp), %ecx
	movb	$49, (%edi,%ecx)
	jmp	L402
L326:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	8(%eax,%esi,4), %eax
	testl	$8192, %eax
	je	L328
	testl	$1, %eax
	je	L329
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC684, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	leal	-24(%ebp), %ecx
	addl	%ecx, %eax
	cmpb	$0, -352(%eax)
	jns	L333
	subl	$352, %eax
	cmpl	$0, 4(%eax)
	jns	L331
	negl	4(%eax)
	movl	12(%ebp), %eax
	movb	$45, (%edi,%eax)
	jmp	L399
L331:
	movl	12(%ebp), %edx
	movb	$43, (%edi,%edx)
L399:
	incl	%edi
	jmp	L333
L329:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testb	$2, 8(%eax,%esi,4)
	je	L334
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC685, 4(%esp)
	jmp	L398
L334:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	testb	$4, 8(%eax,%esi,4)
	je	L336
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC686, 4(%esp)
	jmp	L398
L336:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testb	$64, 8(%eax,%esi,4)
	je	L338
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC687, 4(%esp)
	jmp	L398
L338:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	cmpb	$0, 8(%eax,%esi,4)
	jns	L333
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC688, 4(%esp)
L398:
	call	_sprintf
	addl	%eax, %edi
L333:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC689, 4(%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-372(%ebp,%eax), %eax
L403:
	movl	%eax, 8(%esp)
	jmp	L401
L328:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	movl	8(%eax,%esi,4), %eax
	notl	%eax
	testl	$6307840, %eax
	jne	L342
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC690, 4(%esp)
	movl	-460(%ebp), %eax
	testl	%eax, %eax
	jne	L343
	movl	$LC691, %eax
L343:
	movl	%eax, 8(%esp)
	movl	$LC692, %eax
	cmpl	$0, -460(%ebp)
	jne	L345
	movl	$LC691, %eax
L345:
	movl	%eax, 12(%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	leal	-408(%ebp,%eax), %eax
	cmpl	$32, 8(%eax)
	je	L346
	cmpl	$16, 8(%eax)
	jne	L348
	movl	$LC685, %eax
	jmp	L347
L348:
	movl	$LC691, %eax
	jmp	L347
L346:
	movl	$LC686, %eax
L347:
	movl	%eax, 16(%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-372(%ebp,%eax), %eax
	movl	%eax, 20(%esp)
	call	_sprintf
	addl	%eax, %edi
	movl	$0, -460(%ebp)
	jmp	L311
L342:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	movl	8(%eax,%esi,4), %edx
	movl	%edx, %eax
	notl	%eax
	testl	$2097152, %eax
	jne	L351
	movl	$0, %ebx
	testl	$1, %edx
	je	L352
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC684, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L352:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testb	$2, 8(%eax,%esi,4)
	je	L353
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC685, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L353:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	testb	$4, 8(%eax,%esi,4)
	je	L354
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC686, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L354:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testb	$8, 8(%eax,%esi,4)
	je	L355
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC693, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L355:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	testb	$16, 8(%eax,%esi,4)
	je	L356
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC694, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L356:
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	testb	$32, 8(%eax,%esi,4)
	je	L357
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC695, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L357:
	movl	-444(%ebp), %edx
	movl	(%edx), %eax
	testb	$64, 8(%eax,%esi,4)
	je	L358
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC687, 4(%esp)
	call	_sprintf
	addl	%eax, %edi
L358:
	movl	12(%ebp), %ecx
	movb	$91, (%edi,%ecx)
	incl	%edi
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	leal	-408(%ebp,%eax), %edx
	cmpl	$0, 8(%edx)
	je	L359
	movl	%ecx, %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC682, 4(%esp)
	cmpl	$32, 8(%edx)
	je	L360
	cmpl	$16, 8(%edx)
	jne	L362
	movl	$LC685, %eax
	jmp	L361
L362:
	movl	$LC691, %eax
	jmp	L361
L360:
	movl	$LC686, %eax
L361:
	movl	%eax, 8(%esp)
	call	_sprintf
	addl	%eax, %edi
L359:
	cmpl	$0, -460(%ebp)
	je	L364
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC696, 4(%esp)
	movl	-460(%ebp), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	addl	%eax, %edi
	movl	$0, -460(%ebp)
L364:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	leal	-408(%ebp,%eax), %edx
	cmpl	$-1, 12(%edx)
	je	L365
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC682, 4(%esp)
	movl	12(%edx), %eax
	movl	_reg_names-4(,%eax,4), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	addl	%eax, %edi
	movl	$1, %ebx
L365:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	cmpl	$-1, -392(%ebp,%eax)
	je	L366
	testl	%ebx, %ebx
	je	L367
	movl	12(%ebp), %edx
	movb	$43, (%edi,%edx)
	incl	%edi
L367:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC682, 4(%esp)
	leal	(%esi,%esi,2), %ebx
	sall	$4, %ebx
	leal	-24(%ebp), %ecx
	addl	%ecx, %ebx
	movl	-368(%ebx), %eax
	movl	_reg_names-4(,%eax,4), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	addl	%eax, %edi
	leal	-368(%ebx), %edx
	cmpl	$1, 4(%edx)
	jle	L368
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC697, 4(%esp)
	movl	4(%edx), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	addl	%eax, %edi
L368:
	movl	$1, %ebx
L366:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	leal	-24(%ebp), %edx
	addl	%edx, %eax
	testb	$8, -352(%eax)
	je	L369
	movl	$43, %ecx
	leal	-352(%eax), %edx
	cmpb	$0, 4(%edx)
	jns	L370
	movsbl	4(%edx),%eax
	negl	%eax
	movl	%eax, 4(%edx)
	movl	$45, %ecx
L370:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC698, 4(%esp)
	movl	%ecx, 8(%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-372(%ebp,%eax), %eax
	movl	%eax, 12(%esp)
	call	_sprintf
	jmp	L400
L369:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	testb	$16, -376(%ebp,%eax)
	je	L372
	testl	%ebx, %ebx
	je	L376
	movl	12(%ebp), %ecx
	movb	$43, (%edi,%ecx)
	jmp	L404
L372:
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	testb	$32, -376(%ebp,%eax)
	je	L371
	testl	%ebx, %ebx
	je	L376
	movl	12(%ebp), %eax
	movb	$43, (%edi,%eax)
L404:
	incl	%edi
L376:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC689, 4(%esp)
	leal	(%esi,%esi,2), %eax
	sall	$4, %eax
	movl	-372(%ebp,%eax), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
L400:
	addl	%eax, %edi
L371:
	movl	12(%ebp), %edx
	movb	$93, (%edi,%edx)
L402:
	incl	%edi
	jmp	L311
L351:
	movl	12(%ebp), %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	movl	$LC699, 4(%esp)
	movl	%esi, 8(%esp)
L401:
	call	_sprintf
	addl	%eax, %edi
L311:
	incl	%esi
	movl	-444(%ebp), %ecx
	movl	(%ecx), %eax
	cmpl	4(%eax), %esi
	jl	L378
L391:
	movl	12(%ebp), %eax
	movb	$0, (%edi,%eax)
	cmpl	$0, -460(%ebp)
	je	L379
	movl	%eax, %ecx
	movl	%edi, %edx
	cmpl	$-1, %edi
	je	L393
L383:
	movzbl	(%edx,%ecx), %eax
	movb	%al, 3(%edx,%ecx)
	decl	%edx
	cmpl	$-1, %edx
	jne	L383
L393:
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	-460(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	$2, 8(%esp)
	call	_strncpy
	movl	12(%ebp), %edi
	movb	$32, 2(%edi)
L379:
	movl	-452(%ebp), %eax
L239:
	addl	$524, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
LC700:
	.ascii "db 0x%02X\0"
	.align 2
.globl _eatbyte
	.def	_eatbyte;	.scl	2;	.type	32;	.endef
_eatbyte:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	$LC700, 4(%esp)
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movl	%eax, 8(%esp)
	call	_sprintf
	movl	$1, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
	.comm	_stdin, 16	 # 4
	.comm	_stdout, 16	 # 4
	.comm	_stderr, 16	 # 4
	.comm	_errno, 16	 # 4
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_add_sync;	.scl	2;	.type	32;	.endef
