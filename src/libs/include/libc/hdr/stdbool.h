#if !defined(__OSCA_LIBC_STDBOOL_H__) && !defined( __cplusplus )
#  if !defined( __STDC__ ) /* __STDC__ corresponde a C89/C90 */
  /* Desde C99 en adelante es estandar la definicion
     de enums usando '=' para los valores que representen */
  typedef enum __Bool {
    false=0,
     true=1
  } __packed bool; /* __packed -> macro definida en sys/cdefs.h */
#  else
  /* En C89/C90 no se puede especificar el valor correspondiente,
     los enums aqui comienzan desde 0 en adelante */
  typedef enum __Bool {
    false
     true
  } __packed bool;
#  endif

/* Macros TRUE/FALSE que suelo definir por legibilidad;
   esencialmente son lo mismo que los valores pero es mas comodo
   para usar en #define */
#  if !defined( __false_and_true_defined )
#    define  TRUE                               true
#    define FALSE                              false
#    define __false_and_true_defined            TRUE
#  endif

#  define __OSCA_LIBC_STDBOOL_H__               TRUE
#elif !defined( __OSCA_LIBC_STDBOOL_H__ ) && defined( __cplusplus )
  typedef bool bool; /* Typedef redundante por compatibilidad */

/* Macros TRUE/FALSE que suelo definir por legibilidad;
   esencialmente son lo mismo que los valores pero es mas comodo
   para usar en #define */
#  if !defined( __false_and_true_defined )
#    define  TRUE                               true
#    define FALSE                              false
#    define __false_and_true_defined            TRUE
#  endif
#  define __OSCA_LIBC_STDBOOL_H__               TRUE
#endif