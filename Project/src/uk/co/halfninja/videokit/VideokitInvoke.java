package uk.co.halfninja.videokit;

public final class VideokitInvoke {

  static {
    System.loadLibrary("videokitinvoke");
  }

  public native void run(String path,String[] args);

}
