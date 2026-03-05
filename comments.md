Doxygen works with something called Entities

Description is of type *brief*, *detailed* and *in body*

I decided to use Qt style of code documenting


**Comment block:**
//! Brief entity description
/*!

\* 

\*  \\brief This is brief comment inside block

\*      Brief comment still continues

\*      still continues

\*

\* because there was an empty line, detailed comment begins

\*

*/


//! this is also a brief comment

int x; //!< Brief description of x variable

//!  A test class. 
/*!
  A more elaborate class description.
*/


Example:

//!  A test class. 
/*!
  A more elaborate class description.
*/
class QTstyle_Test
{
  public:

    //! An enum.
    /*! More detailed enum description. */
    enum TEnum { 
                 TVal1, /*!< Enum value TVal1. */  
                 TVal2, /*!< Enum value TVal2. */  
                 TVal3  /*!< Enum value TVal3. */  
               } 
         //! Enum pointer.
         /*! Details. */
         *enumPtr, 
         //! Enum variable.
         /*! Details. */
         enumVar;  

    //! A constructor.
    /*!
      A more elaborate description of the constructor.
    */
    QTstyle_Test();

    //! A destructor.
    /*!
      A more elaborate description of the destructor.
    */
   ~QTstyle_Test();

    //! A normal member taking two arguments and returning an integer value.
    /*!
      \param a an integer argument.
      \param s a constant character pointer.
      \return The test results
      \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
    */
    int testMe(int a,const char *s);

    //! A pure virtual member.
    /*!
      \sa testMe()
      \param c1 the first argument.
      \param c2 the second argument.
    */
    virtual void testMeToo(char c1,char c2) = 0;

    //! A public variable.
    /*!
      Details.
    */
    int publicVar;

    //! A function variable.
    /*!
      Details.
    */
    int (*handler)(int a,int b);
};


\struct to document a C-struct.
\union to document a union.
\enum to document an enumeration type.
\fn to document a function.
\var to document a variable or typedef or enum value.
\def to document a #define.
\file to document a file.
\namespace to document a namespace.
\package to document a Java package.
\interface to document an IDL interface
\a will put word in italic, use for arguments
\attention will start a paragraph witch requires more attention whathever that means
\author 
\b bold font
\brief
\def is used for #define macro
\dir documentation for directory
\enum is used for documenting enumeration
\example : document example of source code
\file
\lineinfo: line number of command
\headerfile
\struct
\typedef
\var variable definition
\bug 
\date
\param[<dir>] <parameter-name> { parameter description }
\return
\test
\version
\pre precondition for something
\post postcondition for something

/*! 
 *  \brief     Pretty nice class.
 *  \details   This class is used to demonstrate a number of section commands.
 *  \author    John Doe
 *  \author    Jan Doe
 *  \version   4.1a
 *  \date      1990-2011
 *  \pre       First initialize the system.
 *  \bug       Not all memory is freed when deleting an object of this class.
 *  \warning   Improper use can crash your application
 *  \copyright GNU Public License.
 */
class SomeNiceClass {};