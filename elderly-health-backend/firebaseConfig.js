// firebaseConfig.js
import admin from "firebase-admin";

const serviceAccount = {
  "type": "service_account",
  "project_id": "rakshak-4b672",
  "private_key_id": "daacb47187c4476cb84f90edb37c7d9db4b46cd8",
  "private_key": "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQD4RR43NJtEDrMb\noIhuodMAAVPBhC1QztZXFFrBWSDkLn9I9NVGBFcCs+rXkzjvsCHMtXpX/pvCm/NM\nz9rTJIdIMiYGXQR8HMLPW7cEokkvQ8nrTePb+MsVRDbl5zzA97soPGsgfgVJ/1Qy\nAbdXO6U9h5Uyk3XEDjU5SbU+AjZy0fzd95GLXv5PzS1aZIj7UfF6dl1yUDnPojNH\niT8ozy8WG3k6ZSL13gUx0FHuxw1wzCUHB+F73BKiq8TWSw94JyX93K9PfAnZMnEb\nZ0DZT0+14NGgGM4b6gh0Ghe7aY34tjPx7n/ZchVF52Wgui8bGXlWEkHrjuesP7Tj\n5aUbrvhjAgMBAAECggEATmVQ9cC8WKDFqO8ntbuOy70fjAdnYdF2eFfakpxI2RTf\np5N8NxhOu3FBsmHwRCubeK9Dmz6wQ6MIEFTANhUeTMtdG3xK2sAgOectox51uqGO\nxKk7Tu5Afo4kQbOjiRGQ/VMaxs9UbznbhdDp6ndQpd3G3IoY0VhlMRpXy2VaeSW7\nmqSr0r9ooB3mIYy0QWyF5KMy4HlGGQWPmxh8nOSJo8qxWcX8r0nn72arTYlhlJAH\nRvBHStvSqA8pcr32sCVR3TROlzZFEbvlKL9doKR013sSU643rmJhpqldqjWjhYxM\n7Iluno2Dv+Yazxiizv/VGbyIoNWTQOtP399FECHt1QKBgQD8alUtlaILkVP01F4Q\np5LtbJJ5AfMIPSzh+JiAIx4uaF4gyEAnCN1iaFCXkQTlj+hNmZNtsXzQ/QS7gYFM\nWFlWdGuD6gqoaIJjgu8Fd3ffGKVG0+//Qh6F2Fog7uV2hzMWlOeuinSZNfWEvXvE\nx2pSAguVDOPUjclGxooo7Q47PwKBgQD7y7bxwc3anxIkHOpsJy2fRslxtQliD4C7\n493wxxIGCYSZvMopLfu3QzdwVskQLwB00Sjwt8WPTDqVsYyHhz7VQ5vcyCq5MJjP\ndQWYv3qB1z6snXqgtsYC1v3eLLLUlcc+xyeF6sgjud+GPBBxGRiXgKNtzpP3MvDp\nkcFU6dRt3QKBgQCiJOAwlyVwDtwCswT1599/OrZgmzr2OO4C/sFf1q9Fmm+U2W40\nZQJpe58BrfuaR7YvWw8UcOZADbijho57b2l8Gu8R3x8XjYLsz6ghN9w96MQK2owZ\nyex3iEJlU3D9kd3kjKTDP1elL79WlK3T+1G1+nBcP9p+qNH58AHCRn1U2wKBgQDx\nVH3CVosTd5SukhxIjoBWgUT/u5EDsHIlIzAL3vCyYpr5so1cTJtOOZlADZ3l6faZ\nAAMqPCiYwGoCIUrcds7NHmCbiioQlrhPVgyIKzWijoeeb80hjixYenCVaef4gpmV\n3NFPtAgg3byT7qufinsccgmxa+Y7blKiurU+ymJ07QKBgDk6Wr+A5NuZvuLnLbwn\n0PJjP3c1EU6qxwgtiRJ22t90rQNaokd2b63YJzf4pf8K1rcYxYaZz1tVEoXIDKDn\n/caNzxbHFMhFwC0s13Fo0RvHXWKkJ8ziPnaEQrmJ+6EheXviCAvBcVd7GonDLgi2\n4UJicy5FcIB/s82QiPhOSdMT\n-----END PRIVATE KEY-----\n",
  "client_email": "firebase-adminsdk-fbsvc@rakshak-4b672.iam.gserviceaccount.com",
  "client_id": "114621481165572761111",
  "auth_uri": "https://accounts.google.com/o/oauth2/auth",
  "token_uri": "https://oauth2.googleapis.com/token",
  "auth_provider_x509_cert_url": "https://www.googleapis.com/oauth2/v1/certs",
  "client_x509_cert_url": "https://www.googleapis.com/robot/v1/metadata/x509/firebase-adminsdk-fbsvc%40rakshak-4b672.iam.gserviceaccount.com",
  "universe_domain": "googleapis.com"
};

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
});

const db = admin.firestore();

console.log("🔥 Firebase initialized successfully!");

export default db;
export { admin, db };