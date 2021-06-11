# remove & rebuild app and macdeploy it

appName="WE-UQ"
appFile="WE_UQ.app"
dmgFile="WE-UQ_Mac_Download.dmg"

QTDIR="/Users/fmckenna/Qt/5.15.2/clang_64/"

pathToBackendApps="/Users/fmckenna/release/SimCenterBackendApplications"
pathToOpenSees="/Users/fmckenna/bin/OpenSees3.2.2"
pathToDakota="/Users/fmckenna/dakota-6.12.0"

#pathToPython="/Users/fmckenna/PythonEnvR2D"

#
# source userID file containig stuff dor signing, ok if not there
#

source userID.sh

#
# build it
#

./makeEXE.sh
cd build

#
# Check to see if the app built
#

if ! [ -x "$(command -v open $pathApp)" ]; then
	echo "$appFile did not build. Exiting."
	exit 
fi

#
# macdeployqt it
#

macdeployqt ./WE_UQ.app 

#
# add missing files from macdeployqt (a known bug)
#


mkdir -p ./$appFile/Contents/plugins/renderers/
cp -R $QTDIR/plugins/renderers/libopenglrenderer.dylib ./$appFile/Contents/plugins/renderers/

echo "cp -R $QTDIR/plugins/renderplugins/libscene2d.dylib ./$appFile/Contents/plugins/renderplugins/"

mkdir -p ./$appFile/Contents/plugins/renderplugins/
cp -R $QTDIR/plugins/renderplugins/libscene2d.dylib ./$appFile/Contents/plugins/renderplugins/


# copy applications folderm opensees and dakota
echo "cp -fR $pathToBackendApps/applications ./$appFile/Contents/MacOS"
cp -fR $pathToBackendApps/applications ./$appFile/Contents/MacOS
mkdir  ./$appFile/Contents/MacOS/applications/opensees
mkdir  ./$appFile/Contents/MacOS/applications/dakota
echo "cp -fr $pathToOpenSees/* $pathApp/Contents/MacOS/applications/opensees"
cp -fr $pathToOpenSees/* ./$appFile/Contents/MacOS/applications/opensees
cp -fr $pathToDakota/*  ./$appFile/Contents/MacOS/applications/dakota

# clean up
declare -a notWantedApp=("createBIM" 
			 "performRegionalMapping"
			 "performRegionalEventSimulation"
			 "performDL"			
			 "createEDP/standardEarthquakeEDP_R"
			 "createEDP/userEDP_R"
			 "createEDP/gmtEDP"			 
			 "createEDP/simpleEDP"
			 "createEDP/standardEarthquakeEDP"
			 "createEVENT/GeoClawOpenFOAM"			 
			 "createEVENT/ASCE7_WindSpeed"
			 "createEVENT/stochasticGroundMotion"
			 "createEVENT/LLNL_SW4"
			 "createEVENT/NNGM"
			 "createEVENT/pointWindSpeed"
			 "createEVENT/hazardBasedEvent"
			 "createEVENT/siteResponse"
			 "createSAM/MDOF-LU"
			 "createSAM/siteResponse"
			 "createSAM/AutoSDA"			 
			 "performSIMULATION/IMasEDP"
			 "performSIMULATION/extractPGA"
			 "performSIMULATION/openSees_R"
			)

for app in "${notWantedApp[@]}"
do
   echo "removing $app"
   rm -fr ./$appFile/Contents/MacOS/applications/$app
done

find ./$appFile -name __pycache__ -exec rm -rf {} +;

#
# load my credential file
#

if [ -z "$appleID" ]; then
    echo "creating dmg $dmgFile"
    rm $dmgFile
    hdiutil create $dmgFile -fs HFS+ -srcfolder ./$appFile -format UDZO -volname $appName

    echo "No password & credential file to continue with codesign and App store verification"
    exit
fi

#codesign
echo "codesign --deep --force --verbose --options=runtime  --sign "$appleCredential" $appFile"
codesign --deep --force --verbose --options=runtime  --sign "$appleCredential" $appFile

# create dmg
echo "hdiutil create $dmgFile -fs HFS+ -srcfolder ./$appFile -format UDZO -volname $appName"
hdiutil create $dmgFile -fs HFS+ -srcfolder ./$appFile -format UDZO -volname $appName

status=$?
if [[ $status != 0 ]]
then
    echo "DMG Creation FAILED cd build and try the following:"
    echo "hdiutil create $dmgFile -fs HFS+ -srcfolder ./$appFile -format UDZO -volname $appName"    
    echo "codesign --force --sign "$appleCredential" $dmgFile"
    echo "xcrun altool --notarize-app -u $appleID -p $appleAppPassword -f ./$dmgFile --primary-bundle-id altool"
    echo "xcrun altool --notarization-info ID  -u $appleID  -p $appleAppPassword"
    echo "xcrun stapler staple \"$appName\" $dmgFile"
    exit $status;
fi

#codesign dmg
echo "codesign --force --sign "$appleCredential" $dmgFile"
codesign --force --sign "$appleCredential" $dmgFile

echo "Issue the following: " 
echo "xcrun altool --notarize-app -u $appleID -p $appleAppPassword -f ./$dmgFile --primary-bundle-id altool"
echo ""
echo "returns id: ID .. wait for email indicating success"
echo "To check status"
echo "xcrun altool --notarization-info ID  -u $appleID  -p $appleAppPassword"
echo ""
echo "Finally staple the dmg"
echo "xcrun stapler staple \"$appName\" $dmgFile"
