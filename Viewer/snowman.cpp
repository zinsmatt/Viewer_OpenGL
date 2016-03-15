#include "snowman.h"
#include "mesh.h"
#include "part.h"
#include "partmanager.h"
#include "utility.h"

SnowMan::SnowMan()
{
	//  snowman = head + body
	//		- body = body + buttons
	//		- head = head + eyes + nose + hat

	PartManager *manager = PartManager::getInstance();

	/* create body assembly */
	Part *body = manager->newPart(true);
	body->getMatrix()->setTranslation(0.0,0.0,2.0);

	/* body part */
	Part *bodyPart = manager->newPart(true);
	bodyPart->createEmptyMesh();
	bodyPart->getMesh()->createSphere(4);
	bodyPart->getMatrix()->setScale(2.0,2.0,2.0);
	bodyPart->setColor(1.0,0.0,0.0);

	/* buttons parts */
	// compute transformations matrices
	Matrixh buttonScale;
	buttonScale.setScale(0.1,0.1,0.1);
	Matrixh buttonTranslate;
	buttonTranslate.setTranslation(2.0,0.0,0.0);
	Matrixh scaleTrans = buttonTranslate * buttonScale;
	Matrixh rotateButton;
	rotateButton.setRotationY(TO_RADIANS(-20));
	Matrixh matButton1 = rotateButton * scaleTrans;
	rotateButton.setRotationY(TO_RADIANS(20));
	Matrixh matButton3 = rotateButton * scaleTrans;

	// create buttons parts
	Part *button1 = manager->newPart(true);
	button1->createEmptyMesh();
	button1->getMesh()->createSphere(4);
	button1->setMatrix(matButton1);

	Part* button2 = manager->newPart(true);
	button2->createEmptyMesh();
	button2->getMesh()->createSphere(4);
	button2->setMatrix(scaleTrans);

	Part *button3 = manager->newPart(true);
	button3->createEmptyMesh();
	button3->getMesh()->createSphere(4);
	button3->setMatrix(matButton3);

	/* add body parts into body assembly */
	body->addSubPart(bodyPart);
	body->addSubPart(button1);
	body->addSubPart(button2);
	body->addSubPart(button3);


	/* create head assembly */
	Part *head = manager->newPart(true);
	head->getMatrix()->setTranslation(0.0,0.0,4.8);

	/* head part */
	Part *headPart = manager->newPart(true);
	headPart->createEmptyMesh();
	headPart->getMesh()->createSphere(4);
	headPart->setColor(1.0,0.0,0.0);

	/* nose part */
	Part *nose = manager->newPart(true);
	nose->createEmptyMesh();
	nose->getMesh()->createCube();
	Matrixh scale;
	scale.setScale(0.1,0.1,0.1);
	Matrixh transl;
	transl.setTranslation(1.0,0.0,0.0);
	Matrixh noseTransf = transl * scale;
	nose->setMatrix(noseTransf);
	nose->setColor(1.0,1.0,1.0);

	/* hat */
	Part *hat = manager->newPart(true);
	hat->createEmptyMesh();
	hat->getMesh()->createCube();
	scale.setScale(0.5,0.5,0.5);
	transl.setTranslation(0.0,0.0,1.0);
	Matrixh hatTransf = transl * scale;
	hat->setMatrix(hatTransf);
	hat->setColor(0.0,0.0,1.0);

	/* eyes */
	// compute transformation matrix
	Matrixh eyeScale;
	eyeScale.setScale(0.1,0.1,0.1);
	Matrixh eyeTransl;
	eyeTransl.setTranslation(1.0,0.0,0.0);
	Matrixh eyeRot;
	eyeRot.setRotationY(TO_RADIANS(-20));
	Matrixh eyeTransf = eyeRot * eyeTransl * eyeScale;

	// create eyes
	Part *eye1 = manager->newPart(true);
	eye1->createEmptyMesh();
	eye1->getMesh()->createSphere(4);
	Matrixh rotz;
	rotz.setRotationZ(TO_RADIANS(-25));
	eye1->setMatrix(rotz * eyeTransf);
	eye1->setColor(1.0,1.0,1.0);

	Part *eye2 = manager->newPart(true);
	eye2->createEmptyMesh();
	eye2->getMesh()->createSphere(4);
	rotz.setRotationZ(TO_RADIANS(25));
	eye2->setMatrix(rotz * eyeTransf);
	eye2->setColor(1.0,1.0,1.0);


	/* add parts into head assembly */
	head->addSubPart(headPart);
	head->addSubPart(eye1);
	head->addSubPart(eye2);
	head->addSubPart(nose);
	head->addSubPart(hat);

	/* add body and head assemblies into snowman assembly */
	this->addSubPart(body);
	this->addSubPart(head);
}

SnowMan::~SnowMan()
{

}

void SnowMan::moveHead(float azimut, float elevation)
{
	// angles in degrees
	azimut = angleMajorValued(azimut);
	elevation = angleMajorValued(elevation);
	if(azimut<-90) azimut = -90;
	if(azimut>90) azimut = 90;

	if(elevation<-90) elevation = -90;
	if(elevation>90) elevation = 90;

	/* follow azimut and elevation */
	Matrixh azimut_mat;
	azimut_mat.setRotationZ(TO_RADIANS(azimut));

	Matrixh elev_mat;
	elev_mat.setRotationY(TO_RADIANS(-(elevation-10)));	//-10 because eyes are not horizontal

	Matrixh	init_mat;	//initial translation
	init_mat.setTranslation(0.0,0.0,5.0);
	Matrixh res = init_mat * azimut_mat * elev_mat;
	subParts[1]->setMatrix(res);	//apply to the head
}
