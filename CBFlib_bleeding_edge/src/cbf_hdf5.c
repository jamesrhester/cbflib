/**********************************************************************
 * cbf_hdf5 -- read and write HDF5/NeXus files                        *
 *                                                                    *
 * Version 0.9.3 21 December 2012                                     *
 *                                                                    *
 *                          Paul Ellis and                            *
 *         Herbert J. Bernstein (yaya@bernstein-plus-sons.com)        *
 *                                                                    *
 * (C) Copyright 2009, 2012 Herbert J. Bernstein                      *
 *                                                                    *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 * YOU MAY REDISTRIBUTE THE CBFLIB PACKAGE UNDER THE TERMS OF THE GPL *
 *                                                                    *
 * ALTERNATIVELY YOU MAY REDISTRIBUTE THE CBFLIB API UNDER THE TERMS  *
 * OF THE LGPL                                                        *
 *                                                                    *
 **********************************************************************/

/*************************** GPL NOTICES ******************************
 *                                                                    *
 * This program is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU General Public License as     *
 * published by the Free Software Foundation; either version 2 of     *
 * (the License, or (at your option) any later version.               *
 *                                                                    *
 * This program is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * along with this program; if not, write to the Free Software        *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA           *
 * 02111-1307  USA                                                    *
 *                                                                    *
 **********************************************************************/

/************************* LGPL NOTICES *******************************
 *                                                                    *
 * This library is free software; you can redistribute it and/or      *
 * modify it under the terms of the GNU Lesser General Public         *
 * License as published by the Free Software Foundation; either       *
 * version 2.1 of the License, or (at your option) any later version. *
 *                                                                    *
 * This library is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 * Lesser General Public License for more details.                    *
 *                                                                    *
 * You should have received a copy of the GNU Lesser General Public   *
 * License along with this library; if not, write to the Free         *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,    *
 * MA  02110-1301  USA                                                *
 *                                                                    *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 *                    Stanford University Notices                     *
 *  for the CBFlib software package that incorporates SLAC software   *
 *                 on which copyright is disclaimed                   *
 *                                                                    *
 * This software                                                      *
 * -------------                                                      *
 * The term �this software�, as used in these Notices, refers to      *
 * those portions of the software package CBFlib that were created by *
 * employees of the Stanford Linear Accelerator Center, Stanford      *
 * University.                                                        *
 *                                                                    *
 * Stanford disclaimer of copyright                                   *
 * --------------------------------                                   *
 * Stanford University, owner of the copyright, hereby disclaims its  *
 * copyright and all other rights in this software.  Hence, anyone    *
 * may freely use it for any purpose without restriction.             *
 *                                                                    *
 * Acknowledgement of sponsorship                                     *
 * ------------------------------                                     *
 * This software was produced by the Stanford Linear Accelerator      *
 * Center, Stanford University, under Contract DE-AC03-76SFO0515 with *
 * the Department of Energy.                                          *
 *                                                                    *
 * Government disclaimer of liability                                 *
 * ----------------------------------                                 *
 * Neither the United States nor the United States Department of      *
 * Energy, nor any of their employees, makes any warranty, express or *
 * implied, or assumes any legal liability or responsibility for the  *
 * accuracy, completeness, or usefulness of any data, apparatus,      *
 * product, or process disclosed, or represents that its use would    *
 * not infringe privately owned rights.                               *
 *                                                                    *
 * Stanford disclaimer of liability                                   *
 * --------------------------------                                   *
 * Stanford University makes no representations or warranties,        *
 * express or implied, nor assumes any liability for the use of this  *
 * software.                                                          *
 *                                                                    *
 * Maintenance of notices                                             *
 * ----------------------                                             *
 * In the interest of clarity regarding the origin and status of this *
 * software, this and all the preceding Stanford University notices   *
 * are to remain affixed to any copy or derivative of this software   *
 * made or distributed by the recipient and are to be affixed to any  *
 * copy of software made or distributed by the recipient that         *
 * contains a copy or derivative of this software.                    *
 *                                                                    *
 * Based on SLAC Software Notices, Set 4                              *
 * OTT.002a, 2004 FEB 03                                              *
 **********************************************************************/



/**********************************************************************
 *                               NOTICE                               *
 * Creative endeavors depend on the lively exchange of ideas. There   *
 * are laws and customs which establish rights and responsibilities   *
 * for authors and the users of what authors create.  This notice     *
 * is not intended to prevent you from using the software and         *
 * documents in this package, but to ensure that there are no         *
 * misunderstandings about terms and conditions of such use.          *
 *                                                                    *
 * Please read the following notice carefully.  If you do not         *
 * understand any portion of this notice, please seek appropriate     *
 * professional legal advice before making use of the software and    *
 * documents included in this software package.  In addition to       *
 * whatever other steps you may be obliged to take to respect the     *
 * intellectual property rights of the various parties involved, if   *
 * you do make use of the software and documents in this package,     *
 * please give credit where credit is due by citing this package,     *
 * its authors and the URL or other source from which you obtained    *
 * it, or equivalent primary references in the literature with the    *
 * same authors.                                                      *
 *                                                                    *
 * Some of the software and documents included within this software   *
 * package are the intellectual property of various parties, and      *
 * placement in this package does not in any way imply that any       *
 * such rights have in any way been waived or diminished.             *
 *                                                                    *
 * With respect to any software or documents for which a copyright    *
 * exists, ALL RIGHTS ARE RESERVED TO THE OWNERS OF SUCH COPYRIGHT.   *
 *                                                                    *
 * Even though the authors of the various documents and software      *
 * found here have made a good faith effort to ensure that the        *
 * documents are correct and that the software performs according     *
 * to its documentation, and we would greatly appreciate hearing of   *
 * any problems you may encounter, the programs and documents any     *
 * files created by the programs are provided **AS IS** without any   *
 * warranty as to correctness, merchantability or fitness for any     *
 * particular or general use.                                         *
 *                                                                    *
 * THE RESPONSIBILITY FOR ANY ADVERSE CONSEQUENCES FROM THE USE OF    *
 * PROGRAMS OR DOCUMENTS OR ANY FILE OR FILES CREATED BY USE OF THE   *
 * PROGRAMS OR DOCUMENTS LIES SOLELY WITH THE USERS OF THE PROGRAMS   *
 * OR DOCUMENTS OR FILE OR FILES AND NOT WITH AUTHORS OF THE          *
 * PROGRAMS OR DOCUMENTS.                                             *
 **********************************************************************/

/**********************************************************************
 *                                                                    *
 *                           The IUCr Policy                          *
 *      for the Protection and the Promotion of the STAR File and     *
 *     CIF Standards for Exchanging and Archiving Electronic Data     *
 *                                                                    *
 * Overview                                                           *
 *                                                                    *
 * The Crystallographic Information File (CIF)[1] is a standard for   *
 * information interchange promulgated by the International Union of  *
 * Crystallography (IUCr). CIF (Hall, Allen & Brown, 1991) is the     *
 * recommended method for submitting publications to Acta             *
 * Crystallographica Section C and reports of crystal structure       *
 * determinations to other sections of Acta Crystallographica         *
 * and many other journals. The syntax of a CIF is a subset of the    *
 * more general STAR File[2] format. The CIF and STAR File approaches *
 * are used increasingly in the structural sciences for data exchange *
 * and archiving, and are having a significant influence on these     *
 * activities in other fields.                                        *
 *                                                                    *
 * Statement of intent                                                *
 *                                                                    *
 * The IUCr's interest in the STAR File is as a general data          *
 * interchange standard for science, and its interest in the CIF,     *
 * a conformant derivative of the STAR File, is as a concise data     *
 * exchange and archival standard for crystallography and structural  *
 * science.                                                           *
 *                                                                    *
 * Protection of the standards                                        *
 *                                                                    *
 * To protect the STAR File and the CIF as standards for              *
 * interchanging and archiving electronic data, the IUCr, on behalf   *
 * of the scientific community,                                       *
 *                                                                    *
 * * holds the copyrights on the standards themselves,                *
 *                                                                    *
 * * owns the associated trademarks and service marks, and            *
 *                                                                    *
 * * holds a patent on the STAR File.                                 *
 *                                                                    *
 * These intellectual property rights relate solely to the            *
 * interchange formats, not to the data contained therein, nor to     *
 * the software used in the generation, access or manipulation of     *
 * the data.                                                          *
 *                                                                    *
 * Promotion of the standards                                         *
 *                                                                    *
 * The sole requirement that the IUCr, in its protective role,        *
 * imposes on software purporting to process STAR File or CIF data    *
 * is that the following conditions be met prior to sale or           *
 * distribution.                                                      *
 *                                                                    *
 * * Software claiming to read files written to either the STAR       *
 * File or the CIF standard must be able to extract the pertinent     *
 * data from a file conformant to the STAR File syntax, or the CIF    *
 * syntax, respectively.                                              *
 *                                                                    *
 * * Software claiming to write files in either the STAR File, or     *
 * the CIF, standard must produce files that are conformant to the    *
 * STAR File syntax, or the CIF syntax, respectively.                 *
 *                                                                    *
 * * Software claiming to read definitions from a specific data       *
 * dictionary approved by the IUCr must be able to extract any        *
 * pertinent definition which is conformant to the dictionary         *
 * definition language (DDL)[3] associated with that dictionary.      *
 *                                                                    *
 * The IUCr, through its Committee on CIF Standards, will assist      *
 * any developer to verify that software meets these conformance      *
 * conditions.                                                        *
 *                                                                    *
 * Glossary of terms                                                  *
 *                                                                    *
 * [1] CIF:  is a data file conformant to the file syntax defined     *
 * at http://www.iucr.org/iucr-top/cif/spec/index.html                *
 *                                                                    *
 * [2] STAR File:  is a data file conformant to the file syntax       *
 * defined at http://www.iucr.org/iucr-top/cif/spec/star/index.html   *
 *                                                                    *
 * [3] DDL:  is a language used in a data dictionary to define data   *
 * items in terms of "attributes". Dictionaries currently approved    *
 * by the IUCr, and the DDL versions used to construct these          *
 * dictionaries, are listed at                                        *
 * http://www.iucr.org/iucr-top/cif/spec/ddl/index.html               *
 *                                                                    *
 * Last modified: 30 September 2000                                   *
 *                                                                    *
 * IUCr Policy Copyright (C) 2000 International Union of              *
 * Crystallography                                                    *
 **********************************************************************/

#ifdef __cplusplus

extern "C" {
    
#endif
    
#include "cbf.h"
#include "cbf_tree.h"
#include "cbf_hdf5.h"
#include "cbf_ascii.h"
#include "cbf_binary.h"
#include "cbf_compress.h"
#include "cbf_file.h"
#include "cbf_write.h"
#include "cbf_write_binary.h"
#include "cbf_read_mime.h"
#include "cbf_string.h"
#include "cbf_codes.h"
#include "cbf_alloc.h"
    
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
    

    
    /* apply a long attribute to a group or dataset */
    
    int cbf_apply_h5long_attribute(hid_t hid,
                                      const char* attribname,
                                      const long attriblong,
                                      int errorcode)
    {
        char buffer[20];
        
        if (attriblong > -10 && attriblong < 10) {
            
            sprintf(buffer,"%ld",attriblong);
            
        } else {
        
            sprintf(buffer,"0x%lx",attriblong);
            
        }

        return cbf_apply_h5text_attribute(hid,attribname,buffer,errorcode);
        
    }

    
    /* apply an integer attribute to a group or dataset */
    
    int cbf_apply_h5integer_attribute(hid_t hid,
                                   const char* attribname,
                                   const int attribint,
                                   int errorcode)
    {
        char buffer[20];
        
        if (attribint > -10 && attribint < 10) {
            
            sprintf(buffer,"%d",attribint);
            
        } else {
            
            sprintf(buffer,"0x%x",attribint);
            
        }
        
        return cbf_apply_h5text_attribute(hid,attribname,buffer,errorcode);
                
    }
   

    
    
    /* apply a text attribute to a group or dataset */
    
    int cbf_apply_h5text_attribute(hid_t hid,
                                   const char* attribname,
                                   const char* attribtext,
                                   int errorcode)
    {
        
        hid_t attribspace, attribtype, attribid;
        
        attribspace = attribtype = attribid = CBF_H5FAIL;
        
        /* ensure arguments all given */
        
        if (hid < 0 || !attribname || !attribtext ) return CBF_ARGUMENT;
        
        cbf_h5reportneg(attribspace = H5Screate(H5S_SCALAR),CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(attribtype = H5Tcopy(H5T_C_S1),CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_size(attribtype,strlen(attribtext)),CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(attribid = H5Acreatex(hid,attribname,
                                        attribtype,
                                        attribspace,
                                        H5P_DEFAULT),
                                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(H5Awrite(attribid,attribtype,
                               (const void *)attribtext),CBF_ALLOC,errorcode);

        if (attribspace >= 0)  H5Sclose(attribspace);
        
        if (attribtype >= 0)   H5Tclose(attribtype);
        
        if (attribid >= 0)     H5Aclose(attribid);
        
        return errorcode;
        
    }
    
    /* Write a binary value to an HDF5 file */
    
    int cbf_write_h5binary (cbf_node *column, unsigned int row,
                            cbf_h5handle h5handle)
    {
        hid_t valid, valtype, valprop, valspace;
        
        int errorcode;

        char rownum[10];

        cbf_file *infile;
        
        char digest [25];
        
        long start;
        
        size_t size;
        
        hsize_t hsize[1];
        
        unsigned int compression;
        
        int id, bits, sign, type, checked_digest, realarray;
        
        const char *byteorder;
        
        size_t dimover, dimfast, dimmid, dimslow;
        
        size_t padding;

        /* Check the arguments */
        
        if (!h5handle || !h5handle->hfile)
            
            return CBF_ARGUMENT;
        
        if (!cbf_is_binary (column, row))
            
            return CBF_ARGUMENT;
        
        if (cbf_is_mimebinary (column, row))
            
            return CBF_ARGUMENT;
        
        cbf_failnez (cbf_get_bintext (column, row, &type, &id, &infile,
                                      &start, &size, &checked_digest,
                                      digest, &bits, &sign, &realarray,
                                      &byteorder, &dimover, &dimfast, &dimmid, &dimslow,
                                      &padding, &compression))

        /* Position the file at the start of the binary section */
        
        cbf_failnez (cbf_set_fileposition (infile, start, SEEK_SET))

        /* Calculate the digest if necessary */
        
        if (!cbf_is_base64digest (digest))
        {
            
            /* Compute the message digest */
            
            cbf_failnez (cbf_md5digest (infile, size, digest))
            
            
            /* Go back to the start of the binary data */
            
            cbf_failnez (cbf_set_fileposition (infile, start, SEEK_SET))
            
            
            /* Update the entry */
            
            checked_digest = 1;
            
            cbf_failnez (cbf_set_bintext (column, row, type,
                                          id, infile, start, size,
                                          checked_digest, digest, bits,
                                          sign,  realarray, 
                                          byteorder, dimover, dimfast, dimmid, dimslow,
                                          padding, compression))
        }
        
        /* Discard any bits in the buffers */
        
        
        infile->bits [0] = 0;
        infile->bits [1] = 0;

        valid = valtype = valprop = valspace = CBF_H5FAIL;

        sprintf(rownum,"%d", row);

        /* prepare the errorcode */
        
        errorcode = 0;
        
        /* Create treat the image as an opaque stream of size bytes */
        
        hsize[0] = size;
        
        cbf_h5reportneg(valspace = H5Screate_simple(1,hsize,NULL),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(valtype = H5Tcreate(H5T_OPAQUE,1),
                        CBF_ALLOC,errorcode);

        cbf_h5reportneg(H5Tset_tag(valtype,"stream of opaque bytes"),
                        CBF_ALLOC,errorcode);
 
                
        cbf_h5reportneg(valprop = H5Pcreate(H5P_DATASET_CREATE),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(valid = H5Dcreatex(h5handle->colid,rownum,
                                          valtype,valspace,
                                          valprop),
                        CBF_ALLOC,errorcode);

        if (!infile->temporary) {

            errorcode |= cbf_get_block(infile,size);
            
        }
        
        
            
        errorcode |= cbf_apply_h5integer_attribute(valid,"compression",compression,errorcode);
        errorcode |= cbf_apply_h5integer_attribute(valid,"binid",id,errorcode);
        errorcode |= cbf_apply_h5integer_attribute(valid,"bits",bits,errorcode);
        errorcode |= cbf_apply_h5integer_attribute(valid,"sign",sign,errorcode);
        errorcode |= cbf_apply_h5integer_attribute(valid,"bintype",type,errorcode);
        errorcode |= cbf_apply_h5text_attribute(valid,"type","bnry",errorcode);
        errorcode |= cbf_apply_h5integer_attribute(valid,"checked_digest",checked_digest,errorcode);
        errorcode |= cbf_apply_h5long_attribute(valid,"size",(long)size,errorcode);
        errorcode |= cbf_apply_h5integer_attribute(valid,"real",realarray,errorcode);
        errorcode |= cbf_apply_h5text_attribute(valid,"byteorder",byteorder,errorcode);
        if (cbf_is_base64digest (digest)) {
            errorcode |= cbf_apply_h5text_attribute(valid,"MD5_digest",digest,errorcode);
        }
        errorcode |= cbf_apply_h5long_attribute(valid,"dimover",(long)dimover,errorcode);
        errorcode |= cbf_apply_h5long_attribute(valid,"dimfast",(long)dimfast,errorcode);
        errorcode |= cbf_apply_h5long_attribute(valid,"dimmid",(long)dimmid,errorcode);
        errorcode |= cbf_apply_h5long_attribute(valid,"dimslow",(long)dimslow,errorcode);
        errorcode |= cbf_apply_h5long_attribute(valid,"padding",(long)padding,errorcode);

        cbf_h5reportneg(H5Dwrite(valid,valtype,
                                 H5S_ALL,H5S_ALL,H5P_DEFAULT,infile->characters),
                        CBF_ARGUMENT,errorcode);
        
        
        if (valid >= 0) {
            
            cbf_h5failneg(H5Dclose(valid),CBF_ARGUMENT);
            
        }
        
        if (valspace >= 0) {
            
            cbf_h5failneg(H5Sclose(valspace),CBF_ARGUMENT);
            
        }
        
        if (valtype >= 0) {
            
            cbf_h5failneg(H5Tclose(valtype),CBF_ARGUMENT);
            
        }
        
        if (valprop >= 0) {
            
            cbf_h5failneg(H5Pclose(valprop),CBF_ARGUMENT);
            
        }
        
        return errorcode;


        
    }

    /* Write an ascii value to an HDF5 file */

    int cbf_write_h5ascii (cbf_handle handle,
                           unsigned int row,
                           const char *string,
                           cbf_h5handle h5handle)
    {
        static const char missing [] = { CBF_TOKEN_WORD, '?', '\0' };
        
 
        hid_t valid, valtype, valprop, valspace;
        
        char rownum[10];
        
        char* typecode;
        
        int errorcode;
        
        /* Check the arguments */
        
        if (!handle || !h5handle || h5handle->hfile < 0) return CBF_ARGUMENT;
        
        valid = valtype = valprop = valspace = CBF_H5FAIL;
        
        sprintf(rownum,"%d", row);
        
        if (!string)
            
            string = missing;
        
        else
            
            if (*string != CBF_TOKEN_WORD       &&
                *string != CBF_TOKEN_SQSTRING   &&
                *string != CBF_TOKEN_DQSTRING   &&
                *string != CBF_TOKEN_SCSTRING   &&
                *string != CBF_TOKEN_TSQSTRING  &&
                *string != CBF_TOKEN_TDQSTRING  &&
                *string != CBF_TOKEN_BKTSTRING  &&
                *string != CBF_TOKEN_BRCSTRING  &&
                *string != CBF_TOKEN_PRNSTRING  &&
                *string != CBF_TOKEN_NULL)
                
                return CBF_ARGUMENT;
        
        /* prepare the errorcode */
        
        errorcode = 0;
        
        /* Create a scalar dataspace */
        
        cbf_h5reportneg(valspace = H5Screate(H5S_SCALAR),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(valtype = H5Tcopy(H5T_C_S1),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(H5Tset_size(valtype,strlen(string+1)),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(valprop = H5Pcreate(H5P_DATASET_CREATE),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(valid = H5Dcreatex(h5handle->colid,rownum,
                        valtype,valspace,valprop),
                        CBF_ALLOC,errorcode);
        
        cbf_h5reportneg(H5Dwrite(valid,valtype,
                        H5S_ALL,H5S_ALL,H5P_DEFAULT,string+1),
                        CBF_ARGUMENT,errorcode);
        
        errorcode |= cbf_get_value_type(string,(const char **)&typecode);
        
        errorcode |= cbf_apply_h5text_attribute(valid,
                        "type",typecode,errorcode);

        if (valid >= 0) {
            
            cbf_h5failneg(H5Dclose(valid),CBF_ARGUMENT);
        
        }
        
        if (valspace >= 0) {
    
            cbf_h5failneg(H5Sclose(valspace),CBF_ARGUMENT);
        
        }
    
        if (valtype >= 0) {

            cbf_h5failneg(H5Tclose(valtype),CBF_ARGUMENT);
            
        }
        
        if (valprop >= 0) {

            cbf_h5failneg(H5Pclose(valprop),CBF_ARGUMENT);
            
        }

        return errorcode;
        
          
    }
    
    /* Write a value to an HDF5 file */
    
    int cbf_write_h5value (cbf_handle handle, cbf_node *column, unsigned int row,
                           cbf_h5handle h5handle)
    {
        const char *text;
                
        /* Check the arguments */
        
        if (!column || !h5handle || h5handle->hfile < 0)
            
            return CBF_ARGUMENT;
        
        if (row >= column->children)
            
            return CBF_NOTFOUND;
        
        
        /* Get the value */
        
        cbf_failnez (cbf_get_columnrow (&text, column, row))
        
        
        /* Missing value? */
        
        if (!text)
            
            return cbf_write_h5ascii (handle, row, text, h5handle);
        
        
        /* Plain ASCII? */
        
        cbf_failnez (cbf_value_type ((char *) text))
        
        if (*text == CBF_TOKEN_WORD     ||
            *text == CBF_TOKEN_SQSTRING ||
            *text == CBF_TOKEN_DQSTRING ||
            *text == CBF_TOKEN_SCSTRING ||
            *text == CBF_TOKEN_TSQSTRING ||
            *text == CBF_TOKEN_TDQSTRING ||
            *text == CBF_TOKEN_PRNSTRING ||
            *text == CBF_TOKEN_BKTSTRING ||
            *text == CBF_TOKEN_BRCSTRING ||
            *text == CBF_TOKEN_NULL)
            
            return cbf_write_h5ascii (handle, row, text, h5handle);
        
        
        /* Plain binary? */
        
        if (*text == CBF_TOKEN_BIN || *text == CBF_TOKEN_TMP_BIN)
            
            return cbf_write_h5binary (column, row, h5handle);
        
        
        /* Undecoded MIME? */
        
        if (*text == CBF_TOKEN_MIME_BIN)
        {
            /* Convert the value to a normal binary section */
            
            cbf_failnez (cbf_mime_temp (column, row))
            
            return cbf_write_h5binary (column, row, h5handle);
        }
        
        
        /* Fail */
        
        return CBF_ARGUMENT;
    }
    
    
    /* Write a category to an HDF5 file */
    
    int cbf_write_h5category (cbf_handle handle,
                              const cbf_node *category,
                              cbf_h5handle h5handle)
    {
        unsigned int column, row;

        /* Check the arguments */
        
        if (!category || !h5handle || h5handle->rootid <0 || h5handle->dbid < 0)
            
            return CBF_ARGUMENT;
        
        
        /* If another category is open, close it */
        
        
        if (h5handle->colid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_FORMAT);
            
            h5handle->colid = CBF_H5FAIL;
            
        }
        
        if (h5handle->catid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->catid),CBF_FORMAT);
            
            h5handle->catid = CBF_H5FAIL;
            
        }
        

        /* Write the name under the opem save frame or datablock */
        
        if (h5handle->sfid <0) {
        
          cbf_h5failneg(h5handle->catid=H5Gcreatex(h5handle->dbid,
                    (category->name)?(category->name):"_(null)_"),
                    CBF_FORMAT);
        
            
        } else {
            cbf_h5failneg(h5handle->catid=H5Gcreatex(h5handle->dbid,
                        (category->name)?(category->name):"_(null)_"),
                        CBF_FORMAT);
            
            
        }
        
        
        cbf_failnez(cbf_apply_h5text_attribute(h5handle->catid,
                                    "NX_class","NXcifcat",0));
        
        
        /* now, for each column, make it into a group and
           store each row as a dataset */
        
        
        for (column= 0; column < category->children; column++)
        {
            
            cbf_h5failneg(h5handle->colid=H5Gcreatex(h5handle->catid,
                        (category->child[column])->name?
                        (category->child[column])->name:"_(null)_"),
                        CBF_FORMAT);
           
            cbf_failnez(cbf_apply_h5text_attribute(h5handle->colid,
                                    "NX_class","NXcifcol",0));
            
            /* For each row, create a dataset */

            for (row=0; row < category->child [column]->children; row++)
            {
                cbf_failnez(cbf_write_h5value(handle,
                                              category->child [column],
                                              row,h5handle));
            }
            
            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_ARGUMENT);

            h5handle->colid = CBF_H5FAIL;
        }
            
        
        /* Success */
        
        return CBF_SUCCESS;

    }
    
    


    /*  create top-level NXentry */

    int cbf_create_NXentry(cbf_h5handle h5handle)
    {
        
        if (!h5handle ||
            h5handle->nxid >= 0 ||
            h5handle->hfile < 0) return CBF_ARGUMENT;
        
        cbf_h5failneg(h5handle->nxid=H5Gcreatex(h5handle->hfile,
                        (const char *)"entry"),
                        CBF_ARGUMENT);
        
        
        cbf_failnez(cbf_apply_h5text_attribute(h5handle->nxid,
                                               "NX_class","NXentry",0));
        
        h5handle->curnxid=CBF_H5FAIL;
        
        return CBF_SUCCESS;
        
    }


    /*  Create an HDF5 Group below NX entry or below curnxid */

    int cbf_H5Gcreate(cbf_h5handle h5handle,
                      const char * groupname,
                      hid_t * newgroup)
    {
        hid_t parent;
        
        if (!h5handle) return CBF_ARGUMENT;
        
        if (h5handle->nxid < 0) {
            
            cbf_failnez(cbf_create_NXentry(h5handle));
            
        }
        
        parent = (h5handle->curnxid >= 0)? h5handle->curnxid: h5handle->nxid;
                
        cbf_h5failneg(*newgroup=H5Gcreatex(parent,groupname),
                    CBF_FORMAT);
        
        return CBF_SUCCESS;
        
    }

    /*  Create an HDF5 NeXus Group below NX entry or below curnxid */
    
    int cbf_H5NXGcreate(cbf_h5handle h5handle,
                        const char * groupname,
                        const char * nxclass,
                        hid_t * newgroup )
    {        
        cbf_failnez(cbf_H5Gcreate(h5handle, groupname, newgroup));
        
        cbf_failnez(cbf_apply_h5text_attribute(*newgroup,
                    "NX_class",nxclass,0));
               
        return CBF_SUCCESS;
        
    }

 
    /* Free an H5File handle */

    int cbf_free_h5handle(cbf_h5handle h5handle) {
        
        void * memblock;
        
        memblock = (void *) h5handle;
        

        if (h5handle->colid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->colid),
                          CBF_UNDEFINED,cbf_free(&memblock,NULL));
            
            
        }

        if (h5handle->catid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->catid),
                          CBF_UNDEFINED,cbf_free(&memblock,NULL));
            
            
        }
        

        if (h5handle->sfid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->sfid),
                          CBF_UNDEFINED,cbf_free(&memblock,NULL));
            
            
        }

        if (h5handle->dbid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->dbid),
                          CBF_UNDEFINED,cbf_free(&memblock,NULL));
            
            
        }

        
        if (h5handle->rootid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->rootid),
                          CBF_UNDEFINED,cbf_free(&memblock,NULL));

            
        }

        if (h5handle->curnxid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->curnxid),
                          CBF_UNDEFINED,cbf_free(&memblock,NULL));

            
        }

        if (h5handle->nxid >= 0) {
            
            cbf_h5onfailneg(H5Gclose(h5handle->nxid),
                            CBF_UNDEFINED,cbf_free(&memblock,NULL));
            
        }

        if (h5handle->hfile >= 0) {
            
            cbf_h5onfailneg(H5Fclose(h5handle->hfile),
                            CBF_FILECLOSE,cbf_free(&memblock,NULL));
            
        }

        return cbf_free(&memblock,NULL);
    }
        
    /* Make an (empty) H5File handle */
        
    int cbf_make_h5handle(cbf_h5handle *h5handle) {
            
            cbf_failnez (cbf_alloc ((void **) h5handle, NULL,
                                      sizeof(cbf_h5handle_struct), 1));
            
            (*h5handle)->hfile   = (hid_t)CBF_H5FAIL;
            (*h5handle)->rootid  = (hid_t)CBF_H5FAIL;
            (*h5handle)->dbid    = (hid_t)CBF_H5FAIL;
            (*h5handle)->sfid    = (hid_t)CBF_H5FAIL;
            (*h5handle)->catid   = (hid_t)CBF_H5FAIL;
            (*h5handle)->colid   = (hid_t)CBF_H5FAIL;
            (*h5handle)->nxid    = (hid_t)CBF_H5FAIL;
            (*h5handle)->curnxid = (hid_t)CBF_H5FAIL;
            (*h5handle)->rwmode  = 0;
        
            return CBF_SUCCESS;

    }

    /* Close the current saveframe in an HDF5 file */
    
    int cbf_close_h5saveframe (cbf_h5handle h5handle)
    {
        
        /* Does the node exist? */
        
        if (!h5handle || h5handle->rootid <0 || h5handle->dbid <0)
            
            return CBF_ARGUMENT;
        
        if (h5handle->colid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_FORMAT);
            
            h5handle->colid = (hid_t)-1;
            
        }
        
        if (h5handle->catid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->catid),CBF_FORMAT);
            
            h5handle->catid = (hid_t)-1;
            
        }
        
        if (h5handle->sfid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->sfid),CBF_FORMAT);
            
            h5handle->sfid = (hid_t)-1;
            
        }
                        
        return CBF_SUCCESS;
    }
    

    /* Write a saveframe name to an HDF5 file
     Make a new group of NeXus class NXcifsf in the NXcif current datablock
     */
    
    int cbf_write_h5saveframename (const cbf_node *saveframe,
                                   cbf_h5handle h5handle)
    {
        
        /* Does the node exist? */
        
        if (!saveframe || !h5handle || h5handle->rootid <0 || h5handle->dbid <0)
            
            return CBF_ARGUMENT;
        
        /* If another saveframe is open, close all its children
         and the saveframe itself */
        
        if (h5handle->sfid >= 0) {
            
            cbf_failnez(cbf_close_h5saveframe(h5handle));
            
        }
        
        
        /* Write the name */
        
        cbf_h5failneg(h5handle->sfid=H5Gcreatex(h5handle->dbid,
                    saveframe->name),
                    CBF_FORMAT);
        
        cbf_failnez(cbf_apply_h5text_attribute(h5handle->sfid,
                    "NX_class", "NXcifsf",0));
        
        return CBF_SUCCESS;
    }
    

    
    
    /* Write a datablock name to an HDF5 file 
       Make a new group of NeXus class NXcifdb in the NXcif class root
     */
    
    int cbf_write_h5datablockname (const cbf_node *datablock, cbf_h5handle h5handle)
    {
        
        /* Does the node exist? */
        
        if (!datablock || !h5handle || h5handle->rootid <0)
            
            return CBF_ARGUMENT;
        
        /* If another datablock is open, close all its children
           and the datablock itself */
        
        if (h5handle->colid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->colid),CBF_FORMAT);
            
            h5handle->colid = (hid_t)-1;

        }
        
        if (h5handle->catid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->catid),CBF_FORMAT);
            
            h5handle->catid = (hid_t)-1;
            
        }

        if (h5handle->sfid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->sfid),CBF_FORMAT);
            
            h5handle->sfid = (hid_t)-1;
            
        }

        if (h5handle->dbid >= 0) {
            
            cbf_h5failneg(H5Gclose(h5handle->dbid),CBF_FORMAT);
            
            h5handle->dbid = (hid_t)-1;
            
        }
        
        /* Write the name */

        cbf_h5failneg(h5handle->dbid=H5Gcreatex(h5handle->rootid,
                                datablock->name),
                                CBF_FORMAT);
        
        cbf_failnez(cbf_apply_h5text_attribute(h5handle->dbid,
                                "NX_class", "NXcifdb",0));
        
        return CBF_SUCCESS;
    }
    

    /* Write a node to an HDF5 file */
    
    int cbf_write_h5node (cbf_handle handle, const cbf_node *node,
                                             const cbf_h5handle h5handle)
    {
        unsigned int count;
        
        
        /* Follow any links */
        
        node = cbf_get_link (node);
        
        
        /* Does the node exist? */
        
        if (!node)
            
            return CBF_ARGUMENT;
        
        /* Node type */
        
        switch (node->type)
        {
                
                
                /* For the root, start the file with a CBF group */
                
            case CBF_ROOT:
                
                break;
                
            case CBF_DATABLOCK:
                
                if (h5handle->rootid < 0) return CBF_FORMAT;
                
                cbf_failnez (cbf_write_h5datablockname (node, h5handle))
                
                break;
                
            case CBF_CATEGORY:
                
                cbf_failnez (cbf_write_h5category (handle, node, h5handle))
                
                break;
                
            case CBF_SAVEFRAME:
                
                cbf_failnez (cbf_write_h5saveframename (node, h5handle))
                
                break;
                
                
            default:
                
                return CBF_ARGUMENT;
        }
        
        
        /* Write the children */
        
        if (node->type == CBF_ROOT || node->type == CBF_DATABLOCK || node->type == CBF_SAVEFRAME)
            
            for (count = 0; count < node->children; count++)
            {
                
                cbf_failnez (cbf_write_h5node (handle, node->child [count], h5handle))
                
            }
        
        if (node->type == CBF_SAVEFRAME) {
            
            cbf_failnez(cbf_close_h5saveframe(h5handle));
            
        }
        
        
        /* Flush the buffers */
        
        cbf_h5failneg(H5Fflush(h5handle->hfile,H5F_SCOPE_LOCAL),CBF_ARGUMENT);
        
        return CBF_SUCCESS;
        
        
    }
    
    

    /* Create an HDF5 File handle */
        
    int cbf_create_h5handle(cbf_h5handle *h5handle,
                              const char * h5filename) {
        
        
        hid_t fcreate_prop_list;
        
        cbf_failnez(cbf_make_h5handle(h5handle));
        
        cbf_h5onfailneg(fcreate_prop_list = H5Pcreate(H5P_FILE_ACCESS),
                        CBF_ALLOC,cbf_free((void**) h5handle, NULL));
        
        (*h5handle)->rwmode = 1;
        
        cbf_h5onfailneg(H5Pset_fclose_degree(fcreate_prop_list,H5F_CLOSE_STRONG),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));
        
        cbf_h5onfailneg((*h5handle)->hfile = H5Fcreate(h5filename,
                        H5F_ACC_TRUNC, H5P_DEFAULT,fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));
        
        cbf_h5onfailneg(H5Pclose(fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));
        
        cbf_onfailnez(cbf_H5Gcreate(*h5handle,"NXcbf",&((*h5handle)->rootid)),
                                    cbf_free_h5handle(*h5handle)); 
        
        return CBF_SUCCESS;
        
    }
        
    
    /*  Write cbf to HDF5 file hfile */
    
    int cbf_write_hdf5_file (cbf_handle handle, cbf_h5handle h5handle)
    {
        cbf_node *node;
                
        if (!handle || !h5handle)
            
            return CBF_ARGUMENT;
        
        /* Find the root node */
        
        cbf_failnez (cbf_find_parent (&node, handle->node, CBF_ROOT))
        
        /* Reset the reference counts */
        
        cbf_failnez( cbf_reset_refcounts(handle->dictionary) )
        
        /* Write the file */
        
        return cbf_write_h5node (handle, node, h5handle);
                        
    }
    
    
    /* Open an HDF5 File handle */
    
    int cbf_open_h5handle(cbf_h5handle *h5handle,
                          const char * h5filename) {
        
        hid_t fcreate_prop_list;
        
        /* check that the file name has been specified and
         is an HDF5 file */
        
        if (!h5filename || !H5Fis_hdf5(h5filename)) return CBF_ARGUMENT;
        
        cbf_failnez(cbf_make_h5handle(h5handle));
        
        cbf_h5onfailneg(fcreate_prop_list = H5Pcreate(H5P_FILE_ACCESS),
                        CBF_ALLOC,cbf_free((void**) h5handle, NULL));
        
        (*h5handle)->rwmode = 0;
        
        cbf_h5onfailneg(H5Pset_fclose_degree(fcreate_prop_list,H5F_CLOSE_STRONG),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));
        
        cbf_h5onfailneg((*h5handle)->hfile = H5Fopen(h5filename,
                                                     H5F_ACC_RDONLY,fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));
        
        cbf_h5onfailneg(H5Pclose(fcreate_prop_list),
                        CBF_ARGUMENT,cbf_free((void**) h5handle, NULL));
        
        return CBF_SUCCESS;
        
    }
    
    /* Convert an HDF5 typeclass to a string 
       and flag for atomic or not 
       copies up to n-1 characters of the
       type string to buffer*/
    
    int cbf_h5type_class_string(H5T_class_t type_class,
                                char * buffer,
                                int * atomic, size_t n ) {
    
        int good_type;
        
        good_type = 0;
        
        *atomic = 1;
        
        buffer[n-1] = '\0';
    
        switch(type_class) {
            case H5T_INTEGER:
                strncpy(buffer,"H5T_INTEGER",n-1);
                break;
            case H5T_FLOAT:
                strncpy(buffer,"H5T_FLOAT",n-1);
                break;
            case H5T_STRING:
                strncpy(buffer,"H5T_STRING",n-1);
                break;
            case H5T_BITFIELD:
                strncpy(buffer,"H5T_BITFIELD",n-1);
                break;
            case H5T_OPAQUE:
                strncpy(buffer,"H5T_OPAQUE",n-1);
                break;
            case H5T_COMPOUND:
                strncpy(buffer,"H5T_COMPOUND",n-1);
                *atomic = 0;
                break;
            case H5T_REFERENCE:
                strncpy(buffer,"H5T_REFERENCE",n-1);
                break;
            case H5T_ENUM:
                strncpy(buffer,"H5T_ENUM",n-1);
                *atomic = 0;
                break;
            case H5T_VLEN:
                strncpy(buffer,"H5T_VLEN",n-1);
                *atomic = 0;
                break;
            case H5T_ARRAY:
                strncpy(buffer,"H5T_ARRAY",n-1);
                *atomic = 0;
                break;
            case -1:
                strncpy(buffer,".",n-1);
                good_type = CBF_ARGUMENT;
                *atomic = 0;
                break;
            default:
                strncpy(buffer,"UNKNOWN",n-1);
                good_type = CBF_ARGUMENT;
                *atomic = 0;
                break;
        }
        
        return good_type;
        
    }
    
    /* Store an HDF5 Dataset in CBF handle, using
       category categoryname, ...*/
    
    int cbf_h5ds_store(cbf_handle handle, haddr_t parent,
                   const char * parent_name,
                   const int target_row,
                   const char * categoryname, hid_t obj_id,
                   hid_t space, hid_t type,
                   const char * name,
                   const int readattrib,
                   char ** value) {
        
        char buffer[25];
        
        unsigned char* data;
        
        char h5t_type_class[14], h5t_base_type_class[14];
                
        hid_t base_type;
        
        hid_t native_type;
        
        int atomic;
        
        int ndims, kdims, ii;
        
        hsize_t dims[H5S_MAX_RANK];

        hsize_t maxdims[H5S_MAX_RANK];
        
        char * byte_order;
                
        size_t type_size, total_size;
        
        H5T_class_t type_class, base_type_class;
        
        H5T_class_t native_type_class;
        
        H5T_order_t type_order;
        
        cbf_failnez(cbf_require_category(handle,categoryname));
        
        /*  Give the name of this dataset as its own id */
        
        cbf_failnez(cbf_require_column(handle,"id"));

        if (target_row==-1) {
              
            cbf_failnez(cbf_new_row(handle));
        
        } else {
            
            cbf_failnez(cbf_select_row(handle,target_row));
        }

        cbf_failnez(cbf_set_value(handle,name));

        /*  Give the parent name and id for this dataset */

        cbf_failnez(cbf_require_column(handle,"parent_name"));
    
        cbf_failnez(cbf_set_value(handle,parent_name));

        cbf_failnez(cbf_require_column(handle,"parent_id"));
        
        sprintf(buffer,"0x%lx",(unsigned long)parent);
        
        cbf_failnez(cbf_set_value(handle,buffer));
        
        
        /* get the class, and, if not atomic
           try to get the base class for an array
           give up otherwise */
        
        type_class = H5Tget_class(type);
        
        base_type = CBF_H5FAIL;
        
        cbf_failnez(cbf_require_column(handle,"type"));
        
        type_size = 0;
        
        if (value) *value = 0;
        
        type_order = -1;
        
        kdims= ndims = H5Sget_simple_extent_ndims(space);
        
        if (ndims <= 0) ndims = 1;
        
        H5Sget_simple_extent_dims(space,dims,maxdims);
        
        if (!cbf_h5type_class_string(
                        type_class,
                        h5t_type_class,&atomic,14)) {
            
            cbf_failnez(cbf_set_value(handle, h5t_type_class));
                                      
            if (!atomic && type_class==H5T_ARRAY){
                base_type = H5Tget_super(type);
                
                base_type_class = H5Tget_class(base_type);
                
                if (!cbf_h5type_class_string(
                        base_type_class,
                        h5t_base_type_class,&atomic,14)) {
                    if (!atomic) {
                        strncpy (h5t_base_type_class,".",14);
                        cbf_h5failneg(H5Tclose(base_type),CBF_FORMAT);
                        base_type = CBF_H5FAIL;
                    } else {
                        
                        type_size = H5Tget_size(base_type);
                        
                        type_order = H5Tget_order(base_type);
                        
                        cbf_failnez(cbf_require_column(handle,"base_type"));

                        cbf_failnez(cbf_set_value(handle,h5t_base_type_class));
                    }
                } else {
                    strncpy (h5t_base_type_class,".",14);
                    cbf_h5failneg(H5Tclose(base_type),CBF_FORMAT);
                    base_type = CBF_H5FAIL;
                }
                
            } else if (atomic) {

                type_size = H5Tget_size(type);
                
                type_order = H5Tget_order(type);
                
            }
            
        }
        
        total_size = type_size;
        
        for (ii=0; ii < kdims; ii ++) {
            
            total_size *= dims[ii];
        }
        
        if (total_size < type_size) total_size = type_size;
        
        cbf_failnez(cbf_require_column(handle,"value"));

        native_type = H5Tget_native_type(type,H5T_DIR_ASCEND);
        
        native_type_class = H5Tget_class(native_type);
        
        if(total_size > 0) {
        
            if(readattrib) {
                
                cbf_failnez(cbf_alloc(((void **) value),NULL,
                                      total_size+1,1));
 
                cbf_h5failneg(H5Aread(obj_id,native_type,(void *)*value),
                              CBF_ARGUMENT);
                
                (*value)[total_size]='\0';
                
                if (native_type_class==H5T_NATIVE_CHAR
                    || native_type_class == H5T_STRING) {
                    
                    cbf_failnez(cbf_set_value(handle,(const char *)(*value)))
                }
              
            } else {
 
                cbf_failnez(cbf_alloc(((void **) &data),NULL,
                                      total_size+1,1));
 
                cbf_h5failneg(H5Dread(obj_id,native_type,
                            H5S_ALL,H5S_ALL,H5P_DEFAULT,data),
                              CBF_ARGUMENT);
                
                data[total_size]='\0';

                if (native_type_class==H5T_NATIVE_CHAR
                    || native_type_class == H5T_STRING) {
                    
                    cbf_failnez(cbf_set_value(handle,(const char *)data))
                }
                
            }

        }
        switch(type_order) {
            case H5T_ORDER_LE:
                byte_order = "H5T_ORDER_LE";
                break;
            case H5T_ORDER_BE:
                byte_order = "H5T_ORDER_BE";
                break;
            case H5T_ORDER_VAX:
                byte_order = "H5T_ORDER_VAX";
                break;
            case H5T_ORDER_MIXED:
                byte_order = "H5T_ORDER_MIXED";
                break;
            case H5T_ORDER_NONE:
                byte_order = "H5T_ORDER_LE";
                break;
            case -1:
                byte_order = ".";
                break;
            default: byte_order="UNKNOWN";
                break;
        }
        
        cbf_failnez(cbf_require_column(handle,"h5_byte_order"));
        
        cbf_failnez(cbf_set_value(handle,byte_order));

        if (type_size < 10) {
            
            sprintf(buffer,"%ld",(unsigned long)type_size);
            
        } else {
            
            sprintf(buffer,"0x%lx",(unsigned long)type_size);
            
        }

        cbf_failnez(cbf_require_column(handle,"size"));
        
        cbf_failnez(cbf_set_value(handle,buffer));
        
        if (base_type >=0) H5Tclose(base_type);
        
        if (native_type>=0) H5Tclose(native_type);
        
        return CBF_SUCCESS;
    }


    /* Callback routine for objects in a group */


    herr_t cbf_object_visit(hid_t loc_id, const char *name,
                            const H5L_info_t *info,
                            void *op_data){
        
        cbf_handle handle;
        
        haddr_t parent_addr;
        
        hid_t parent_id;
        
        unsigned int row;
        
        const char* parent_name;
        
        hid_t group_id, dataset_id;
        
        herr_t retval;
        
        hsize_t i;
        
        char buffer[25];
        
        char digest[25];
        
        char *value;
        
        H5O_info_t  objinfo;
        
        hid_t attrib_id,attrib_ds,attrib_type;
        
        hid_t dataset_ds, dataset_type;
        
        ssize_t attrib_name_size;
        
        int attrib_num;
        
        unsigned int compression;
        
        int binary_id, bits, sign, type, checked_digest, realarray;
        
        const char *byteorder;
        
        size_t binsize;
        
        size_t dimover, dimfast, dimmid, dimslow;
        
        size_t padding;
        
        handle = ((cbf_h5Ovisithandle)op_data)->handle;
        
        if (!handle) return -1;
        
        /* skip the root group itself */
        
        if (name[0]== '.') return 0;
        
        cbf_h5failneg(H5Oget_info_by_name(loc_id,
                                          name, &objinfo, H5P_DEFAULT),CBF_FORMAT);
        parent_id = ((cbf_h5Ovisithandle)op_data)->parent_id;
        
        parent_addr = ((cbf_h5Ovisithandle)op_data)->parent_addr;
        
        parent_name = ((cbf_h5Ovisithandle)op_data)->parent_name;

        switch (objinfo.type) {
                
            case H5O_TYPE_GROUP:
                
                /* Skip duplicates */
                
                for (i=0; i < ((cbf_h5Ovisithandle)op_data)->path_size; i++) {
                    
                    if (objinfo.addr ==
                        ((cbf_h5Ovisithandle)op_data)->haddr_path[i])
                        return 0;
                    
                }
                
                if (((cbf_h5Ovisithandle)op_data)->path_size >=
                    ((cbf_h5Ovisithandle)op_data)->capacity) {
                    
                    size_t newcap;
                    
                    newcap = 2*((cbf_h5Ovisithandle)op_data)->capacity;
                    
                    cbf_failnez(
                                cbf_realloc(
                                            (void **)(&((cbf_h5Ovisithandle)op_data)->hid_path),
                                            NULL,sizeof(hid_t),newcap));
                    cbf_failnez(
                                cbf_realloc(
                                            (void **)(&((cbf_h5Ovisithandle)op_data)->haddr_path),
                                            NULL,sizeof(haddr_t),newcap));
                    
                    ((cbf_h5Ovisithandle)op_data)->capacity=newcap;
                    
                }
                
                (((cbf_h5Ovisithandle)op_data)->
                 haddr_path)[((cbf_h5Ovisithandle)op_data)->path_size] =
                objinfo.addr;
                
                group_id = H5Gopenx(loc_id,name);
                (((cbf_h5Ovisithandle)op_data)->
                 haddr_path)[((cbf_h5Ovisithandle)op_data)->path_size] =
                group_id;
                (((cbf_h5Ovisithandle)op_data)->path_size)++;
                
                /* We have a group
                 We need to add it to the H5_Groups category
                 in the current data block.
                 
                 If it has attributes, we need to add them to
                 the H5Attributes category
                 
                 If it has datasets, we will catch them when we
                 iterate again
                 
                 */
                
                cbf_failnez(cbf_require_category(handle,"H5_Groups"));
                
                cbf_failnez(cbf_new_row(handle));
                
                cbf_failnez(cbf_row_number(handle,&row));
                
                cbf_failnez(cbf_require_column(handle,"name"));
                
                cbf_failnez(cbf_set_value(handle,name));
                
                cbf_failnez(cbf_require_column(handle,"parent_name"));
                
                cbf_failnez(cbf_set_value(handle,parent_name));

                cbf_failnez(cbf_require_column(handle,"parent_id"));
                
                if (!parent_addr) {
                    
                    cbf_failnez(cbf_set_value(handle,"."));
                                        
                    cbf_failnez(cbf_set_typeofvalue(handle,"null"));
 
                } else {
                    
                    sprintf(buffer,"0x%lx",(unsigned long)parent_addr);
                    
                    cbf_failnez(cbf_set_value(handle,buffer));
                    
                }

                cbf_failnez(cbf_require_column(handle,"id"));
                
                sprintf(buffer,"0x%lx",(unsigned long)objinfo.addr);
                
                cbf_failnez(cbf_set_value(handle,buffer));
                
                attrib_num = objinfo.num_attrs;
                
                cbf_failnez(cbf_require_column(handle,"no_attributes"));
                
                cbf_failnez(cbf_set_integervalue(handle,attrib_num));
                
                for (i=0; i < attrib_num; i++) {
                
                    char * attrib_name;
                    attrib_id=H5Aopen_by_idx(group_id,".",
                                H5_INDEX_NAME,
                                H5_ITER_INC,
                                i,H5P_DEFAULT,H5P_DEFAULT);
                    attrib_ds = H5Aget_space(attrib_id);
                    attrib_type = H5Aget_type(attrib_id);
                    attrib_name_size = H5Aget_name(attrib_id,0,NULL);
                    cbf_failnez(cbf_alloc(((void **) &attrib_name),NULL,
                                          attrib_name_size+1,1));
                    
                    cbf_h5failneg(H5Aget_name(attrib_id,
                                              attrib_name_size+1,attrib_name),
                                  CBF_ARGUMENT);
                    cbf_h5ds_store(handle,objinfo.addr,
                                   name,-1,
                                   "H5_Group_attribute",
                                   attrib_id,
                                   attrib_ds,
                                   attrib_type,
                                   attrib_name,1, &value);
                    if (!cbf_cistrcmp(attrib_name,"NX_class")&& value) {
                        
                        cbf_failnez(cbf_require_category(handle,"H5_Groups"));
                        
                        cbf_failnez(cbf_find_column(handle,"id"));
                        
                        cbf_failnez(cbf_select_row(handle,row));
                        
                        cbf_failnez(cbf_require_column(handle,"NX_class"));
                        
                        cbf_failnez(cbf_set_value(handle,value));
                        
                    }
                    
                    cbf_failnez(cbf_free((void **)&attrib_name,NULL));
                    if (value) {
                        cbf_failnez(cbf_free((void **)&value, NULL));
                    }
                    H5Tclose(attrib_type);
                    H5Sclose(attrib_ds);
                    H5Aclose(attrib_id);
                }
                
                ((cbf_h5Ovisithandle)op_data)->parent_addr = objinfo.addr;
                
                ((cbf_h5Ovisithandle)op_data)->parent_id = group_id;
                
                cbf_failnez(cbf_alloc(((void **) &(((cbf_h5Ovisithandle)op_data)->parent_name)),NULL,
                                      strlen(name)+1,1));
                
                strcpy((char *)((cbf_h5Ovisithandle)op_data)->parent_name,name);
                
                retval = H5Literate_by_name(loc_id, name,H5_INDEX_NAME,
                                            H5_ITER_INC,
                                            NULL,
                                            cbf_object_visit,op_data,H5P_DEFAULT);
                
                H5Gclose(group_id);
                
                cbf_failnez(cbf_free((void **)(&((cbf_h5Ovisithandle)op_data)->parent_name),NULL));
                
                (((cbf_h5Ovisithandle)op_data)->path_size)--;

                ((cbf_h5Ovisithandle)op_data)->parent_id = parent_id;
                
                ((cbf_h5Ovisithandle)op_data)->parent_addr = parent_addr;
                
                ((cbf_h5Ovisithandle)op_data)->parent_name = parent_name;
                
                return retval;
                break;
                
            case H5O_TYPE_DATASET:
                
                dataset_id = H5Dopen2(loc_id,name,H5P_DEFAULT);

              /* We have a dataset
                 We need to add it to the H5_Datasets category
                 in the current data block.
                 
                 If it has attributes, we need to add them to
                 the H5_Attributes category
                                  
                 */
                
                cbf_failnez(cbf_require_category(handle,"H5_Datasets"));
                
                cbf_failnez(cbf_new_row(handle));
                
                cbf_failnez(cbf_row_number(handle,&row));
                
                cbf_failnez(cbf_require_column(handle,"name"));
                
                cbf_failnez(cbf_set_value(handle,name));
                
                cbf_failnez(cbf_require_column(handle,"parent_name"));
                
                cbf_failnez(cbf_set_value(handle,parent_name));
                
                cbf_failnez(cbf_require_column(handle,"parent_id"));
                
                if (!parent_addr) {
                    
                    cbf_failnez(cbf_set_value(handle,"."));
                    
                    cbf_failnez(cbf_set_typeofvalue(handle,"null"));
                    
                } else {
                    
                    sprintf(buffer,"0x%lx",(unsigned long)parent_addr);
                    
                    cbf_failnez(cbf_set_value(handle,buffer));
                    
                }
                
                cbf_failnez(cbf_require_column(handle,"id"));

                sprintf(buffer,"0x%lx",(unsigned long)objinfo.addr);
                
                cbf_failnez(cbf_set_value(handle,buffer));
                
                attrib_num = objinfo.num_attrs;
 
                cbf_failnez(cbf_require_column(handle,"no_attributes"));
                
                cbf_failnez(cbf_set_integervalue(handle,attrib_num));
                
                dimover = 0;
               
                for (i=0; i < attrib_num; i++) {
                    
                    char * attrib_name;
                    attrib_id=H5Aopen_by_idx(dataset_id,".",
                                             H5_INDEX_NAME,
                                             H5_ITER_INC,
                                             i,H5P_DEFAULT,H5P_DEFAULT);
                    attrib_ds = H5Aget_space(attrib_id);
                    attrib_type = H5Aget_type(attrib_id);
                    attrib_name_size = H5Aget_name(attrib_id,0,NULL);
                    cbf_failnez(cbf_alloc(((void **) &attrib_name),NULL,
                                          attrib_name_size+1,1));
                    
                    cbf_h5failneg(H5Aget_name(attrib_id,
                                              attrib_name_size+1,attrib_name),
                                  CBF_ARGUMENT);
                    cbf_h5ds_store(handle,objinfo.addr,
                                   name,-1,
                                   "H5_Dataset_attribute",
                                   attrib_id,
                                   attrib_ds,
                                   attrib_type,
                                   attrib_name,1,&value);
                    if (*value) {
                        
                        cbf_failnez(cbf_require_category(handle,"H5_Datasets"));
                        
                        cbf_failnez(cbf_find_column(handle,"id"));

                        cbf_failnez(cbf_select_row(handle,row));
                        
                        cbf_failnez(cbf_require_column(handle,attrib_name));
                        
                        cbf_failnez(cbf_set_value(handle,value));
                        
                        if (!cbf_cistrcmp(attrib_name,"compression")) {
                            compression=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"binid")) {
                            binary_id=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"bits")) {
                            bits=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"sign")) {
                            sign = (int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"bintype")) {
                            type=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"checked_digest")) {
                            checked_digest=(int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"real")) {
                            realarray = (int)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"byteorder")) {
                            byteorder=
                            (value[0]=='l'||value[0]=='L')?
                            "little_endian":"big_endian";
                        } else if (!cbf_cistrcmp(attrib_name,"size")) {
                            binsize = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"digest")) {
                            strcpy(digest,value);
                        } else if (!cbf_cistrcmp(attrib_name,"dimover")) {
                            dimover = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"dimfast")) {
                            dimfast = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"dimmid")) {
                            dimmid = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"dimslow")) {
                            dimslow = (size_t)strtol(value,NULL,0);
                        } else if (!cbf_cistrcmp(attrib_name,"padding")) {
                            padding = (size_t)strtol(value,NULL,0); 
                        }
                    }
                                       
                    cbf_failnez(cbf_free((void **)&attrib_name,NULL));
                    if (value) cbf_failnez(cbf_free((void **)&value, NULL));
                    H5Tclose(attrib_type);
                    H5Sclose(attrib_ds);
                    H5Aclose(attrib_id);
                }
               
                dataset_ds = H5Dget_space(dataset_id);
                dataset_type = H5Dget_type(dataset_id);

                cbf_h5ds_store(handle,objinfo.addr,
                               parent_name,row,
                               "H5_Datasets",
                               dataset_id,
                               dataset_ds,
                               dataset_type,
                               name,0,&value);
                
                if (binsize&&value) {
                    
                    size_t elsize, nelem;
                    
                    cbf_node * column;
                    
                    cbf_file *tempfile;
                    
                    long start;
                    
                    elsize = (bits+CHAR_BIT-1)/CHAR_BIT;
                    
                    nelem = (binsize+elsize-1)/elsize;
                    
                    if (dimover <=0) dimover = nelem;
                    
                    if (nelem > 0 && elsize > 0) {
                        
                        cbf_failnez(cbf_require_category(handle,"H5_Datasets"));
                        
                        cbf_failnez(cbf_find_column(handle,"id"));
                        
                        cbf_failnez(cbf_select_row(handle,row));
                        
                        cbf_failnez(cbf_require_column(handle,"value"));
                        
                        column = handle->node;
                        
                        
                        /* Remove the old value */
                        
                        cbf_failnez (cbf_set_columnrow (column, row, NULL, 1))
                        
                        
                        /* Get the temporary file */
                        
                        cbf_failnez (cbf_open_temporary (column->context, &tempfile))
                        
                        
                        /* Move to the end of the temporary file */
                        
                        if (cbf_set_fileposition (tempfile, 0, SEEK_END))
                            
                            return CBF_FILESEEK | cbf_delete_fileconnection (&tempfile);
                        
                        
                        /* Get the starting location */
                        
                        if (cbf_get_fileposition (tempfile, &start))
                            
                            return CBF_FILETELL | cbf_delete_fileconnection (&tempfile);
                        
                        
                        /* Discard any bits in the buffers */
                        
                        cbf_failnez (cbf_reset_bits (tempfile))

                        
                        /* Add the binary data to the temporary file */
                        
                        if (!cbf_set_output_buffersize(tempfile,nelem))  {
                            
                            memmove((void *)(tempfile->characters+tempfile->characters_used),
                                    (void *)value,binsize);
                            
                            tempfile->characters_used+=binsize;
                            
                        }
                        
                        cbf_onfailnez(cbf_set_bintext(column,row,CBF_TOKEN_TMP_BIN,
                                                   binary_id,tempfile,start,binsize,
                                                   1,digest,bits,sign,realarray,byteorder,
                                                   dimover, dimfast, dimmid, dimslow,
                                                 padding,compression),
                                      cbf_delete_fileconnection (&tempfile));
                        
                    }
                }
                if (value) cbf_failnez(cbf_free((void **)&value, NULL));
                H5Dclose(dataset_id);
                H5Sclose(dataset_ds);
                H5Tclose(dataset_type);

                break;
                
            case H5O_TYPE_NAMED_DATATYPE:
                
                break;
                
            default:
                
                return CBF_FORMAT;
                
                
                
        }
        return 0;
    }
    /* Read an HDF5 file */
    
    int cbf_read_h5file(cbf_handle handle, cbf_h5handle h5handle) {
        
        cbf_node *node;
        
        cbf_h5Ovisit_struct h5Ovisit;
        
        if (!handle || !h5handle || !h5handle->hfile ) return CBF_ARGUMENT;
        
        /* Delete the old datablocks */
        
        if( handle->commentfile) cbf_failnez (cbf_free_file (&(handle->commentfile)));
        
        cbf_failnez (cbf_find_parent (&node, handle->node, CBF_ROOT));
        
        cbf_failnez (cbf_set_children (node, 0))
        
        handle->node = node;
        
        cbf_failnez (cbf_reset_refcounts(handle->dictionary));
        
        
        h5Ovisit.handle = handle;
        
        h5Ovisit.h5handle = h5handle;
        
        h5Ovisit.parent_addr = 0;
        
        h5Ovisit.parent_id = h5handle->hfile;
        
        h5Ovisit.parent_name = "/";

        cbf_failnez(cbf_alloc ((void **) (&(h5Ovisit.hid_path)), NULL,
                               sizeof(hid_t), 1));

        cbf_failnez(cbf_alloc ((void **) (&(h5Ovisit.haddr_path)), NULL,
                               sizeof(haddr_t), 1));
                    
        h5Ovisit.capacity = 1;
        
        h5Ovisit.path_size = 0;
        
        cbf_failnez(cbf_new_datablock(handle,"H5"));

        /* visit the groups in the file, starting with the root group */
        
        cbf_h5failneg(H5Literate(h5handle->hfile,
                               H5_INDEX_NAME,
                               H5_ITER_INC,
                               NULL,
                               cbf_object_visit,(void *)&h5Ovisit),CBF_FORMAT);
        
        return CBF_SUCCESS;
        
    }



    
#ifdef __cplusplus
    
}

#endif
