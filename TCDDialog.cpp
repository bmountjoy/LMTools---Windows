// TCDDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LMTools.h"
#include "TCDDialog.h"
#include "afxdialogex.h"

// TCDDialog dialog
IMPLEMENT_DYNAMIC(TCDDialog, CDialogEx)

TCDDialog::TCDDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TCD_DIALOG, pParent)
{

}

TCDDialog::~TCDDialog()
{
}

void TCDDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(TCDDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &TCDDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// TCDDialog message handlers
void TCDDialog::OnBnClickedOk()
{
	CString filePath = "";

	// Open a TIFF file
	GDALDataset* ds =
		(GDALDataset*)GDALOpen((const char*)CT2A(filePath).m_psz, GDALAccess::GA_ReadOnly);

	if (ds == NULL)
	{
		AfxMessageBox(_T("Failed to open the TIFF file!"), MB_OK | MB_ICONSTOP);
		return;
	}
	
	GDALClose(ds);

	// Open a Shape file

	OGRDataSource *shapeDS;
	shapeDS = OGRSFDriverRegistrar::Open("point.shp", FALSE);
	if (shapeDS == NULL)
	{
		AfxMessageBox(_T("Failed to open the ShapeFile!"), MB_OK | MB_ICONSTOP);
		return;
	}

	OGRLayer  *poLayer;
	poLayer = shapeDS->GetLayerByName("point");

	OGRFeature *poFeature;

	poLayer->ResetReading();
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
		int iField;

		for (iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(iField);

			if (poFieldDefn->GetType() == OFTInteger)
				printf("%d,", poFeature->GetFieldAsInteger(iField));
			else if (poFieldDefn->GetType() == OFTReal)
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));
			else if (poFieldDefn->GetType() == OFTString)
				printf("%s,", poFeature->GetFieldAsString(iField));
			else
				printf("%s,", poFeature->GetFieldAsString(iField));
		}

		OGRGeometry *poGeometry;

		poGeometry = poFeature->GetGeometryRef();
		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbPoint)
		{
			OGRPoint *poPoint = (OGRPoint *)poGeometry;

			printf("%.3f,%3.f\n", poPoint->getX(), poPoint->getY());
		}
		else
		{
			printf("no point geometry\n");
		}
		OGRFeature::DestroyFeature(poFeature);
	}

	OGRDataSource::DestroyDataSource(shapeDS);

	AfxMessageBox(_T("Something bad happened!"), MB_OK | MB_ICONSTOP);
}
