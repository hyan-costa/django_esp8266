import datetime

from django.shortcuts import render, HttpResponse
from django.views.decorators.csrf import csrf_exempt

@csrf_exempt
def get_data(request):
    if request.method=="POST":
        print(request.POST.get('luz'), datetime.datetime.now())
        return render(request,'test.html')
    if request.method=="GET":
        print(request)
        return render(request,'test.html')