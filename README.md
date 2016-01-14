# Open-Source-Sim-Stethoscope
Information and code for a Stethoscope to be used in medical training

Background

In health care, a Simulated Participant, Standardized Patient, or Sample Patient (referred to as an SP) is an individual trained to act as a real patient in order to simulate a set of symptoms or problems. Simulated Patients have been used in the education and evaluation of an array of health care providers including nursing, medical, pharmacy and social work learners.

The standardized patients are taught to deliver specific patient case information to learners. The standardized patients communicate and deliver the patient’s history in a way that meets the needs of the specific learning experience (usually orally or using simulated patient records). The history portion of the SP simulation experience can be reproduced with effective standardized patients and retains a high fidelity to typical patient encounters.

However during the encounter, the SP is not able to simulate certain physical findings that the learner may try obtain by examination: for example, an abnormal eye exam, a heart murmurs, abdominal noises, or crackling lung sounds. These findings must be delivered by means other than observation and interrupts the patient encounter. The lack of realism can introduce disruption and may present a less authentic experience

In this project, we are specifically looking for methods to improve the delivery physical findings and represent physical elements of a SP in a way that continues to assist the learner in a realistic patient encounter. As such we first inventoried the methods by which findings are, and could be, delivered to the learner:

 

Option1Option 1.

Find ‘real’ patients with abnormal findings that the students could examine and practice their skills. This would represent one of the best possible solutions, but is unrealistic for several reasons:

Lack of available patients who would be willing to serve as standard patients.
Any such SPs would be limited in the encounter experiences they could provide (a one-trick pony so to speak).
Option2Option 2.

Find standardized patients with medical conditions to fulfill the role for learning experiences. An example, find standardized patients with fundoscopy eye exam abnormalities. Find standardized patients for death and dying scenarios find standardized patients that have experience with abdominal cancerous masses.

As with Option 1, while this might represent one of the best scenarios for findings delivery, it is unrealistic.

 Option3Option 3

Utilize a normal healthy standardized patient to represent history and some physical findings and represent hard to recreate physical findings through paper findings cards. Patients physical medical findings are delivered to a participant when appropriately triggered. The standardized patient delivers paper-based findings cards during encounter. Using this method the SP can deliver findings card that states ”heart murmur found in M3” or “lungs sounds are crackling”. These paper cards can be held by the patient and deliver to the learner during an encounter. This is the currently used system at the simulation center. This has several problems/risks:

The SP can drop or mix up the cards.

 

The learner does have the opportunity to come in contact with the patient in the same way they would in a “real world” encounter.

The learner doesn’t have the opportunity

Option4Option 4

Utilize a normal healthy standardized patient to represent history and some physical findings and represent hard to recreate physical findings through electronically generated methods. The standardized patient delivers electronic based findings through a tablet device during the encounter. The method allows the standardized patient to select and present a mix of digital content including images, sounds or video into the experience of the learner. This can be accomplished by the standardized patient presenting the appropriate electronic content via a computer or tablet device when the learner asks to investigate a specific physical aspect of the human body.

Option5Option 5

Utilize a normal healthy standardized patient to represent history and some physical findings and represent hard to recreate physical findings through electronically generated methods. An additional standardized assistant can remotely view the live interaction between learner and standardized patient and then identifies triggers and delivers electronic based findings through a tablet or computer device during the encounter. The method allows the standardized patient to focus on representing the history part of the encounter and a remote assistant then triggers the appropriate digital content including images, sounds or video into the experience of the learner. This can be accomplished by the remote assistant presenting the appropriate electronic content via a computer or tablet device when the learner asks to investigate a specific physical aspect of the human body.

 

Option6Option 6

Utilize a normal healthy standardized patient to represent history and some physical findings and represent hard to recreate physical findings through electronically generated methods. Allow the learner to select the electronic based findings through a tablet device during the encounter. The method allows the learner to select and observe a mix of digital content including images, sounds or video into the experience. This can be accomplished by the learner selecting appropriate electronic content via a computer or tablet device when investigating a specific physical aspect of the human body.

Option 7

Option7Utilize a normal healthy standardized patient to represent history and some physical findings and represent hard to recreate physical findings through electronically generated methods. The standardized patient can deliver electronic based physical findings through defined voice commands to an in room computer device during the encounter. The method allows the standardized patient to command the display of digital content including images, sounds or video into the experience of the learner. This can be accomplished by the standardized patient triggering voice commands for appropriate electronic content via a computer or tablet device when the learner asks to investigate a specific physical aspect of the human body.

Option 8

Option8Utilize a normal healthy standardized patient to represent history and some physical findings and represent hard to recreate physical findings through electronically generated methods. The standardized patient is outfitted with an array of sensors (QR codes, lights sensors, pressure sensors) to detect learner interaction. Based on the learners interaction sets of sensors and processors, sound output and displays can represent the appropriate electronic content. One example, would be use of a stethoscope that plays the appropriate content when placed in the correct location for lung or heart sounds.

After considering the options, we focused on developing a project to develop an open source hardware and software project to deliver findings triggered via a sensor (Option 8).
