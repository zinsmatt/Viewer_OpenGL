#include "snowman.h"
#include "mesh.h"
#include "part.h"
#include "assembly.h"
#include "partmanager.h"
#include "utility.h"
#include "matrixh.h"
#include "material.h"

SnowMan::SnowMan(int id) : Assembly(id)
{
	//  snowman = head + body
	//		- body = body + buttons
	//		- head = head + eyes + nose + hat

	PartManager *manager = PartManager::getInstance();

	/* create body assembly */
	Assembly *body = manager->newAssembly(true);
	body->getMatrix()->setTranslation(0.0,0.0,2.0);

	/* body part */
	Part *bodyPart = manager->newPart(true);
	bodyPart->getMesh()->createSphere(4);
	bodyPart->getMatrix()->setScale(2.0,2.0,2.0);
	bodyPart->setColor(1.0,0.0,0.0);
	Material* mat = bodyPart->getMaterial();
	mat->setAmbient(1.0,1.0,1.0,1.0);
	mat->setDiffuse(1.0,1.0,1.0,1.0);
	mat->setSpecular(1.0,1.0,1.0,1.0);
	mat->setShininess(100.0);

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
	button1->getMesh()->createSphere(4);
	button1->setMatrix(matButton1);
	button1->getMaterial()->setAmbient(0.0,0.0,0.0,1.0);

	Part* button2 = manager->newPart(true);
	button2->getMesh()->createSphere(4);
	button2->setMatrix(scaleTrans);
	button2->getMaterial()->setAmbient(0.0,0.0,0.0,1.0);

	Part *button3 = manager->newPart(true);
	button3->getMesh()->createSphere(4);
	button3->setMatrix(matButton3);
	button3->getMaterial()->setAmbient(0.0,0.0,0.0,1.0);

	/* add body parts into body assembly */
	body->addSubPart(bodyPart);
	body->addSubPart(button1);
	body->addSubPart(button2);
	body->addSubPart(button3);


	/* create head assembly */
	Assembly *head = manager->newAssembly(true);
	head->getMatrix()->setTranslation(0.0,0.0,4.8);

	/* head part */
	Part *headPart = manager->newPart(true);
	headPart->getMesh()->createSphere(4);
	headPart->setColor(1.0,0.0,0.0);
	mat = headPart->getMaterial();
	mat->setAmbient(1.0,1.0,1.0,1.0);
	mat->setDiffuse(1.0,1.0,1.0,1.0);
	mat->setSpecular(1.0,1.0,1.0,1.0);
	mat->setShininess(100.0);


	/* nose part */
	Part *nose = manager->newPart(true);
	nose->getMesh()->createCone(8,1,1);
	Matrixh scale;
	scale.setScale(0.1,0.1,0.3);
	Matrixh rotation;
	rotation.setRotationY(TO_RADIANS(90));
	Matrixh transl;
	transl.setTranslation(1.0,0.0,0.0);
	Matrixh noseTransf = transl * rotation * scale;
	nose->setMatrix(noseTransf);
	nose->setColor(1.0,1.0,1.0);
	nose->getMaterial()->setAmbient(1.0,0.17,0.0,1.0);
	nose->getMaterial()->setDiffuse(1.0,0.17,0.0,1.0);

	/* hat */
	Part *hat = manager->newPart(true);
	hat->getMesh()->createCone(20,2.0);
	scale.setScale(0.5,0.5,0.5);
	transl.setTranslation(0.0,0.0,0.8);
	Matrixh hatTransf = transl * scale;
	hat->setMatrix(hatTransf);
	hat->setColor(0.0,0.0,1.0);
	hat->getMaterial()->setAmbient(0.0,0.0,1.0,1.0);
	hat->getMaterial()->setDiffuse(0.0,0.0,1.0,1.0);
	hat->getMaterial()->setSpecular(0.5,0.5,0.5,1.0);
	hat->getMaterial()->setShininess(1);

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
	eye1->getMesh()->createSphere(4);
	Matrixh rotz;
	rotz.setRotationZ(TO_RADIANS(-25));
	eye1->setMatrix(rotz * eyeTransf);
	eye1->setColor(1.0,1.0,1.0);
	eye1->getMaterial()->setAmbient(0.0,0.0,0.0,1.0);
	eye1->getMaterial()->setDiffuse(0.0,0,0,1.0);
	eye1->getMaterial()->setSpecular(0.001,0.001,0.001,1.0);
	eye1->getMaterial()->setShininess(128);

	Part *eye2 = manager->newPart(true);
	eye2->getMesh()->createSphere(4);
	rotz.setRotationZ(TO_RADIANS(25));
	eye2->setMatrix(rotz * eyeTransf);
	eye2->setColor(1.0,1.0,1.0);
	eye2->getMaterial()->setAmbient(0.0,0.0,0.0,1.0);
	eye2->getMaterial()->setDiffuse(0.0,0.0,0.0,1.0);
	eye2->getMaterial()->setSpecular(1.0,1.0,1.0,1.0);
	eye2->getMaterial()->setShininess(128);


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

void SnowMan::showInfo() const
{
	std::cout << "(SnowMan)" << std::endl;
	Assembly::showInfo();
}
