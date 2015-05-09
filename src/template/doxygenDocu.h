#pragma once
/*! \mainpage XBMC ADSP Addon Handling & Template Documentation
 *
 * \section overview_sec Overview
 * This documentation describes how to setup XBMC with 
 * Audio Digital Signal Processing (ADSP) addons and how to start developing for it.
 * At the moment of writting there only exist a branch of XBMC for that 
 * (<a href="https://github.com/AlwinEsch/xbmc/tree/audio-dsp-addon-handling">AlwinEsch's 
 * audio-dsp-addon-handling modification</a> ).
 * We hope that this modifications will be added to XBMC master repository very soon.
 *
 * \section reference_sec Reference
 * - If you wanna compile XBMC with alwinus modifications see \ref how_to_compile_page. <br>
 * - For more informations about how to develop a ADSP addon see \ref how_to_develop_page.
 * - If you wanna know how to use the ADSP addon modification in the view of an user then 
 * you have to follow the instructions in \ref how_to_use_adsp_addons_page.
 *
 * \section todo_sec Things to do 
 * The ADSP handling in XBMC and the template are almost finished,
 * but there are things to do for more details see \ref todo.
 *
 * \subsection license_sec License
 * @author     wisler (ADSP addon developer), wislerelectronics@googlemail.com
 * @author	   alwinus (ADSP XBMC addong handling & ADSP addon developer), email@email.com
 * @date       April 22, 2014
 */

/*! \page how_to_compile_page How to compile XBMC with ADSP addon handling
 * \tableofcontents
 * \section win_sec Compiling for Windows
 * ToDo!
 *
 * \section linux_sec Compiling for Linux
 * ToDo!
 *
 * \section mac_os_x_sec Compiling for MAC OS X
 * Find someone who can compile and test XBMC with ADSP addon handling under MAC OS X.
*/


/*! \page how_to_develop_page How to develop a ADSP addon for XBMC
 * \tableofcontents
 * \section introduction_sec Introduction
 * The ADSP addon API is quite complex and the prefered way is to build the template first.
 * So you can see if all is working. After that you can use the template as a starting point and
 * implement your algorithm into the template. On the other hand you can write your own wrapper
 * class and use the template as a reference.
 *
 * \section software_sec Prerequisites
 * \subsection Software for Windows
 * \subsection Software for Linux
 * \subsection Software for MAC OS X
 * \section how_to_get_ADSP_template_sec How to get ADSP addon template
 * \section processing_modes_sec Processing modes
 * \subsection input_processing_mode_sec Input processing mode description
 * ToDo
 *
 * \section how_to_use_adsp_addon_sec How to use your ADSP addon
 * ToDo <br>
 *
 * \section templateConfiguration_h_sec How to configure the template
 * ToDo <br>
 * For more details see templateConfiguration.h.
 *
 * \section templateConfiguration_cpp_sec How to configure processing modes
 * ToDo <br>
 * For more details see templateConfiguration.cpp.
 *
 * \section own_processing_class_sec How to create your own processing class
 * ToDo <br>
 * You can implement your own or use the CDSPProcessor class as an starting point.
 *
 * \section own_optional_class_sec How to create your own optional class
 * ToDo <br>
 * You can implement your own or use the CADDONOptional class as an starting point.
 * 
*/

/*! \page how_to_use_adsp_addons_page How to use the ADSP addon handling modification (user perspective)
 * \tableofcontents
 * \section enable_disable_sec Enable or Disable an ADSP addon (XBMC's addon manager)
 * ToDo
 *
 * \section DSP_manager_sec How to use the DSP Manager
 * At the moment of writting the GUI is not complete. When it is finish this section will
 * be extended.
 *
 * \section listening_mode_sec How to enable signal processing while playing media files
 * ToDo
*/