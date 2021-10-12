(define clone vector-copy)

(define u8vector 4)
(define s8vector 8)
(define u16vector 5)
(define s16vector 9)
(define u32vector 6)
(define s32vector 10)
(define u64vector 7)
(define s64vector 11)
(define f32vector 2)
(define f64vector 3)
(define (cadr x) (car (cdr x)))
(define (cddr x) (cdr (cdr x)))
(define (caddr x) (car (cddr x)))
(define (cdddr x) (cdr (cddr x)))
(define (cadddr x) (car (cdddr x)))
(define (cddddr x) (cdr (cdddr x)))
(define (caddddr x) (car (cddddr x)))
(define (cdddddr x) (cdr (cddddr x)))

;(define-syntax record (lambda (vars vals exp)
;	`((lambda ,vars ,exp) ,vals)))

(defvar self (current-envobj))

(define-syntax record
  (lambda (x)
    `((lambda ,(car x) ,(caddr x)) ,(cadr x))))

;(define-syntax defmacro
;  (lambda (x)
;    (begin
;;      (display "\ndefmacro  ")
;;      (display x)
;;      (display "\n\n")
;      (syntax-case x ()
;		   ((defmacro name args body)
;		    (begin
;;		      (display "\ndefmacro2\n")
;		      `(define-syntax ,name
;			 (lambda (x)
;			   (syntax-case x () ((,name ,@args) ,body))))))))))

(define-syntax defmacro (lambda ((_ name args body)) `(define-syntax ,name (lambda ((_ ,@args)) ,body)) ))

(defmacro defobject (name parents . body)
  `(define ,name (begin ,@body (current-envobj))))

(defmacro function (name args . forms)
  `(define (,name ,@args) ,@forms))

(define (syntax-object->datum x) x)

(defmacro record (vars vals exp)
  `((lambda ,vars ,exp) ,vals))

(defmacro pattern-case-2 (key patterns)
  (if (null? patterns) #z
      `(if (match? ,key ,(car (car patterns))) ,(cdr (car patterns))
	   ,(pattern-case-2 key (cdr patterns)) )) )

;(defmacro pattern-case (key . patterns)
;	(let (kn (gensym))
;		`(let ((,kn ,key)) ())))

defmacro print args
	let inner