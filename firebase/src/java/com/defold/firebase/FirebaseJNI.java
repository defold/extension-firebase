package com.defold.firebase;

import androidx.annotation.NonNull;
import android.app.Activity;
import android.util.Log;

import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.firebase.installations.FirebaseInstallations;
import com.google.firebase.installations.InstallationTokenResult;

import org.json.JSONObject;
import org.json.JSONException;


public class FirebaseJNI {
    private static final String TAG = "FirebaseJNI";

    public static native void firebaseAddToQueue(int msg, String json);

    // duplicate of enums from firebase_callback.h:
    // CONSTANTS:
    private static final int MSG_ERROR =                   0;
    private static final int MSG_INITIALIZED =             1;
    private static final int MSG_INSTALLATION_AUTH_TOKEN = 2;
    private static final int MSG_INSTALLATION_ID =         3;

    private Activity activity;

    public FirebaseJNI(Activity activity) {
        this.activity = activity;
    }

    public void initialize() {
        // TODO do we need to call FIR init explicitly? 
        sendSimpleMessage(MSG_INITIALIZED);
    }

    public void getInstallationAuthToken() {
        FirebaseInstallations.getInstance().getToken(false).addOnCompleteListener(new OnCompleteListener<InstallationTokenResult>() {
            @Override
            public void onComplete(@NonNull Task<InstallationTokenResult> task) {
                if (task.isSuccessful() && task.getResult() != null) {
                    sendSimpleMessage(MSG_INSTALLATION_AUTH_TOKEN, "token", task.getResult().getToken());
                } else {
                    sendErrorMessage("Unable to get Installation auth token");
                }
            }
        });		
    }

    public void getInstallationId() {
        FirebaseInstallations.getInstance().getId().addOnCompleteListener(new OnCompleteListener<String>() {
            @Override
            public void onComplete(@NonNull Task<String> task) {
                if (task.isSuccessful()) {
                    sendSimpleMessage(MSG_INSTALLATION_ID, "id", task.getResult());
                } else {
                    sendErrorMessage("Unable to get Installation ID");
                }
            }
        });
    }

    // https://www.baeldung.com/java-json-escaping
    private String getJsonConversionErrorMessage(String errorText) {
        String message = null;
        
        try {
            JSONObject obj = new JSONObject();
            obj.put("error", errorText);
            message = obj.toString();
        } catch (JSONException e) {
            message = "{ \"error\": \"Error while converting simple message to JSON.\"}";
        }

        return message;
    }

    private void sendErrorMessage(String errorText) {
        String message = getJsonConversionErrorMessage(errorText);
        Log.d(TAG, "FIR Error");
        Log.d(TAG, message);
        firebaseAddToQueue(MSG_ERROR, message);
    }

    private void sendSimpleMessage(int msg) {
        firebaseAddToQueue(msg, "{}");
    }

    private void sendSimpleMessage(int msg, String key, String value) {
        String message = null;

        try {
            JSONObject obj = new JSONObject();
            obj.put(key, value);
            message = obj.toString();
            firebaseAddToQueue(msg, message);
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getLocalizedMessage());
            firebaseAddToQueue(MSG_ERROR, message);
        }
    }    
}