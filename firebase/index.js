const { spawn } = require('child_process');
const admin = require('firebase-admin');
const fs = require('fs');

admin.initializeApp({
    credential: admin.credential.cert('pathtoserviceaccountkey.json'),
    databaseURL: 'projectid.firebaseio.com'
});

const db = admin.firestore();

async function checkFlag(uid) {
    const localFlag = readLocalFlag();

    if (localFlag !== null) {
        console.log(`Local flag value: ${localFlag}`);
        return localFlag;
    }


    const docRef = db.collection('settings').doc(uid);
    const doc = await docRef.get();

    if (!doc.exists) {
        console.log('No such document in cloud');
        return false;
    }

    const flag = doc.data().flag;
    console.log(`firestore flag value: ${flag}`)
    return flag;
}





//keep going here