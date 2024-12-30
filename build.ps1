Push-Location .
$build_dir = 'build'

if (-Not (Test-Path -Path $build_dir)) {
  mkdir $build_dir
}

Set-Location $build_dir
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Debug --parallel 2

if (-Not ($LASTEXITCODE -eq "0")) {
  Write-Output "cmake --build for Debug mode failed!"
  Pop-Location
  exit 1
}

Pop-Location
exit 0